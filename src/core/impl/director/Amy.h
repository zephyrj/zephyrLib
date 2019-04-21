#pragma once

#include <Director.h>

namespace zephyr { namespace core {
class Workshop;
  
class Director::Amy final
{
public:
  explicit Amy(Workshop* workshop);
  ~Amy();

  Amy(const zephyr::core::Director::Amy&) = delete;
  Amy& operator=(const zephyr::core::Director::Amy&) = delete;

  void schedule_work(const std::function<void(void)>& workItem) const;
  void schedule_work(std::function<void(void)>&& workItem);

  void start_work();
  void stop_work();

private:
  Workshop* m_workshop;

};
  
}}