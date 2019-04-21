#include <Director.h>
#include <impl/director/Amy.h>

namespace zephyr { namespace core {
  
Director::Director(Workshop* workshop)
  : m_appointedDirector_p(std::make_unique<Director::AppointedDirector>(workshop))
{}

Director::~Director() = default;

void Director::schedule_work(const std::function<void(void)>& workItem)
{
  m_appointedDirector_p->schedule_work(workItem);
}

void Director::schedule_work(std::function<void(void)>&& workItem)
{
  m_appointedDirector_p->schedule_work(std::move(workItem));
}

void Director::start_work()
{
  m_appointedDirector_p->start_work();
}

void Director::stop_work()
{
  m_appointedDirector_p->stop_work();
}

}}