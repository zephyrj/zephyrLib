#ifndef ZEPHYR_ASYNC_FRAMEWORK_HPP
#define ZEPHYR_ASYNC_FRAMEWORK_HPP

#include <memory>
#include <type_traits>

#include <boost/asio/io_service.hpp>

#include <ScopedPointer.hpp>
#include <mutex>
#include <thread>

namespace zephyr { namespace async {

namespace framework { class Component; }

class Framework
{
  friend class framework::Component;

public:
  explicit Framework();
  Framework(const Framework&) = delete;
  Framework& operator=( const Framework& ) = delete;

  virtual ~Framework() = default;

  void run();
  void shutdown();

  bool isRunning();

  template <typename T, typename... Args>
  ScopedPointer<T> addComponent(Args &&... args)
  {
    static_assert(std::is_base_of<framework::Component, T>::value,
                  "Only objects that derive from the framework::Component object can be added to the Framework");
    return zephyr::make_scoped<T>(*this, std::forward<Args>(args)...);
  };

private:
  static void workerThread(Framework *framework_p);

  boost::asio::io_service &getIOService() __attribute__((pure));

  void componentAdded(framework::Component* component);
  void componentRemoved(framework::Component* component);

  std::atomic_bool running;

  mutable std::mutex components_mutex;
  std::vector<framework::Component*> components;

  std::shared_ptr<boost::asio::io_service> io_service;
  std::shared_ptr<boost::asio::io_service::work> io_service_work;

  std::thread* worker_thread;

};

}}

#endif
