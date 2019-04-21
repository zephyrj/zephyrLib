#pragma once

#include <memory>
#include <functional>

namespace zephyr { namespace core {
class Workshop;

class Director
{
public:
  explicit Director(Workshop* workshop);
  ~Director();

  void schedule_work(const std::function<void(void)>& workItem);
  void schedule_work(std::function<void(void)>&& workItem);

  void start_work();
  void stop_work();
  
private:
  class Amy;
  using AppointedDirector = Amy;
  
  std::unique_ptr<AppointedDirector> m_appointedDirector_p;
  
};
  
}}