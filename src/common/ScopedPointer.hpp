#ifndef ZEPHYR_SCOPEDPOINTER_HPP
#define ZEPHYR_SCOPEDPOINTER_HPP

#include <boost/intrusive_ptr.hpp>
#include <boost/atomic.hpp>

namespace zephyr {

/*!
 *  \brief This class is basically just a shared_ptr that can be wrapped by a boost::intrusive_ptr
 *         with the notable exception of it calling shutdown on the stored object when the destructor is
 *         called.
 *
 *  The purpose of this class is for it to be used inside an zephyr::async::framework::ScopedPointer
 *  It implements the functions that allow it to be contained in an intrusive_ptr whilst also storing a shared_ptr to
 *  the object that is to be encapsulated inside the ScopedPointer.
 *
 *  The reason this wrapper is needed is so that an object can shut itself down once all references to it go
 *  out of scope.
 *
 *  The user will get a ScopedPointer to an object and will use that pointer until they don't require the object it
 *  points to anymore. Once the ScopedPointer goes out of scope it will call the destructor on this ScopedWrapper object
 *  - this in turn will call the shutdown method on the internal type and the shared_ptr reference will go out of scope.
 *  The object encapsulated by this wrapper must provide a shutdown method. This shutdown method is expected to
 *  destroy any outstanding references to the object and allow it to go out of scope and have it's destructor called.
 *
 *  An example to explain why this is needed would be an object that uses the shared_from_this() construct in order to
 *  use a boost asynchronous function safely. If the object was passed around with a regular shared_ptr and all
 *  references outside of the asynchronous handler went out of scope it there will still be an outstanding shared_ptr
 *  referencing the object in the asynchronous callback mechanism. This means that you would have to explicitly call
 *  some function on the object in order to cancel the asynchronous operation before it can be destroyed by RAII.
 *
 *  Calling shutdown() from this wrapper class allows us to cancel any outstanding asynchronous callbacks without the
 *  user of the object having to it explicitly; thus making it less likely that bugs will arise from shutdown actions
 *  not being performed.
 */
template <typename InternalType>
class ScopedWrapper final
{
  // todo This could do with having a move constructor/assignment operator set up for it
public:
  ScopedWrapper(std::shared_ptr<InternalType> p) : refcount_(0),
                                                   shared_ptr(p)
  {}

  std::shared_ptr<InternalType> operator->() const
  {
    return shared_ptr;
  }

  InternalType& operator*()
  {
    return *shared_ptr;
  }

protected:
  ~ScopedWrapper()
  {
    shared_ptr->shutdown();
  }

private:
  mutable boost::atomic<int> refcount_;
  std::shared_ptr<InternalType> shared_ptr;

  friend void intrusive_ptr_add_ref(const ScopedWrapper<InternalType>* x)
  {
    x->refcount_.fetch_add(1, boost::memory_order_relaxed);
  }

  friend void intrusive_ptr_release(const ScopedWrapper<InternalType>* x)
  {
    if (x->refcount_.fetch_sub(1, boost::memory_order_release) == 1)
    {
      boost::atomic_thread_fence(boost::memory_order_acquire);
      delete x;
    }
  }
};

/*!
 *  \brief This class takes all of its functionality from an intrusive pointer but
 *         hides the fact that there is a ScopedWrapper between this object and the InternalType
 *         from users of the class.
 */
template <typename InternalType>
class ScopedPointer : public boost::intrusive_ptr<ScopedWrapper<InternalType>>
{
public:

  // Make sure we call the intrusive_ptr default/copy/move constructors

  // Empty constructor
  ScopedPointer()
      : boost::intrusive_ptr<ScopedWrapper<InternalType>>()
  {}

  // Regular constructor
  ScopedPointer(ScopedWrapper<InternalType>* p)
      : boost::intrusive_ptr<ScopedWrapper<InternalType>>(p)
  {}

  // Copy constructor
  ScopedPointer(ScopedPointer<InternalType> const & rhs)
      : boost::intrusive_ptr<ScopedWrapper<InternalType>>(rhs)
  {}

  // Move constructor
  ScopedPointer(ScopedPointer<InternalType> && rhs)
      : boost::intrusive_ptr<ScopedWrapper<InternalType>>(rhs)
  {}

  // Destructor
  virtual ~ScopedPointer() = default;

  // Move assignment
  ScopedPointer & operator=(ScopedPointer && rhs)
  {
    boost::intrusive_ptr<ScopedWrapper<InternalType>>::operator=(rhs);
    return *this;
  }

  // copy assignment
  ScopedPointer & operator=(ScopedPointer const & rhs)
  {
    boost::intrusive_ptr<ScopedWrapper<InternalType>>::operator=(rhs);
    return *this;
  }

  ScopedPointer & operator=(ScopedPointer * rhs)
  {
    boost::intrusive_ptr<ScopedWrapper<InternalType>>::operator=(rhs);
    return *this;
  }

  // Override these operators to make the ScopedWrapper invisible to the caller
  // We are hiding the base class operators as they are not virtual but this won't be
  // a problem as only this class will be exposed to the caller.
  // i.e. they won't be called on the base class.

  ScopedWrapper<InternalType>& operator->() const
  {
    return *(this->get());
  }

  InternalType& operator*() const
  {
    ScopedWrapper<InternalType>& p = *(this->get());
    return *p;
  }

  std::shared_ptr<InternalType> getSharedInternalType()
  {
    return this->get()->operator->();
  }
};

template <typename T, typename... Args>
ScopedPointer<T> make_scoped(Args &&... args)
{
  std::shared_ptr<T> sharedPointer = std::make_shared<T>(std::forward<Args>(args)...);
  ScopedWrapper<T>* wrapper = new ScopedWrapper<T>(sharedPointer);
  return ScopedWrapper<T>(wrapper);
};

}

#endif
