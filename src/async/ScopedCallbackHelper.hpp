#ifndef ZEPHYRLIB_ASYNC_SCOPEDCALLBACKHELPER_HPP
#define ZEPHYRLIB_ASYNC_SCOPEDCALLBACKHELPER_HPP

#include <exception>
#include <atomic>
#include <mutex>
#include <boost/thread/pthread/shared_mutex.hpp>

namespace {

template <typename Callable>
class callback_wrapper final : public std::enable_shared_from_this<callback_wrapper<Callable>>
{
public:
  callback_wrapper(Callable&& callable,
                   std::shared_ptr<std::atomic_bool> canExecute,
                   std::shared_ptr<boost::shared_mutex> callbackExecutionMutex)
          : m_callable(std::forward<Callable>(callable)),
            m_can_execute(std::move(canExecute)),
            m_callback_in_progress_execution_mutex(std::move(callbackExecutionMutex))
  {}

  ~callback_wrapper() = default;

  template <typename... Args>
  void operator()(Args&&... args)
  {
    if(! m_can_execute->load(std::memory_order_acquire)) return;

    boost::shared_lock<boost::shared_mutex> lock(*m_callback_in_progress_execution_mutex);
    m_callable(std::forward<Args>(args)...);
  }

  template <typename... Args>
  void operator()(const Args&... args) const
  {
    if(! m_can_execute->load(std::memory_order_acquire)) return;

    boost::shared_lock<boost::shared_mutex> lock(*m_callback_in_progress_execution_mutex);
    m_callable(std::forward<Args>(args)...);
  }

private:
  Callable m_callable;

  mutable std::shared_ptr<std::atomic_bool> m_can_execute;
  mutable std::shared_ptr<boost::shared_mutex> m_callback_in_progress_execution_mutex;

};

}

namespace zephyr { namespace async {

class ScopedCallbackHelper final
{
public:
  ScopedCallbackHelper() : m_can_execute_callbacks(std::make_shared<std::atomic_bool>(true)),
                           m_callback_in_progress_execution_mutex(std::make_shared<boost::shared_mutex>())
  {}

  ~ScopedCallbackHelper()
  {
    m_can_execute_callbacks->store(false, std::memory_order_release);
    boost::unique_lock<boost::shared_mutex> lock(*m_callback_in_progress_execution_mutex);
  }

  template <typename Callable>
  callback_wrapper<Callable> createCallback(Callable&& callable)
  {
    return callback_wrapper<Callable>(std::forward<Callable>(callable),
                                      m_can_execute_callbacks,
                                      m_callback_in_progress_execution_mutex);
  }

private:
  mutable std::shared_ptr<std::atomic_bool> m_can_execute_callbacks;
  mutable std::shared_ptr<boost::shared_mutex> m_callback_in_progress_execution_mutex;

};

}}

#endif
