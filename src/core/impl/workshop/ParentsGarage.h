#pragma once

#include <Workshop.h>
#include <atomic>

namespace {
  constexpr size_t get_max_number_of_workers() { return 24; }
}

namespace boost { namespace asio { class io_service; }}

namespace zephyr { namespace core {
  
class Workshop::ParentsGarage final
{
public:
  ParentsGarage();
  ~ParentsGarage();

  void async_start_work();
  void stop_work();

  void add_worker();

  void add_to_work_queue(const std::function<void(void)>& workItem);
  void add_to_work_queue(std::function<void(void)>&& workItem);

private:
  std::unique_ptr<boost::asio::io_service> m_workQueue_p;
  
  struct Worker;
  std::array<std::unique_ptr<Worker>, get_max_number_of_workers()> m_workers;
  std::atomic<size_t> m_numberOfConfiguredWorkers;

  std::atomic_bool m_working;
    
};
  
}}