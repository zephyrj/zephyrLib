#include "Amy.h"
#include "Workshop.h"

namespace zephyr { namespace core {
  
Director::Amy::Amy(Workshop* workshop) : m_workshop(workshop)
{
  m_workshop->add_worker();
}
  
Director::Amy::~Amy() = default;

void Director::Amy::schedule_work(const std::function<void(void)>& workItem) const
{
  m_workshop->add_to_work_queue(workItem);
}

void Director::Amy::schedule_work(std::function<void(void)>&& workItem)
{
  m_workshop->add_to_work_queue(std::move(workItem));
}

void Director::Amy::start_work()
{
  m_workshop->async_start_work();
}

void Director::Amy::stop_work()
{
  m_workshop->stop_work();
}
  
}}
