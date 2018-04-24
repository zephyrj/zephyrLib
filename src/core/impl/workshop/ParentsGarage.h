#pragma once

#include <Workshop.h>

namespace {
  constexpr size_t get_max_number_of_workers() { return 24; }
}

namespace boost { class thread_group;
namespace asio { class io_service; }}

namespace zephyr { namespace core {
  
class Workshop::ParentsGarage final
{
public:
  ParentsGarage();
  ~ParentsGarage();

  void async_start_work();
  void stop_work();

  void add_worker();

private:
  std::unique_ptr<boost::asio::io_service> m_workQueue_p;
  
  struct Worker;
  std::array<std::unique_ptr<Worker>, get_max_number_of_workers()> m_workers;
  size_t m_numberOfConfiguredWorkers;
    
};
  
}}