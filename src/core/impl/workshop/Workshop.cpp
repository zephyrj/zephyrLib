#include <Workshop.h>
#include <impl/workshop/ParentsGarage.h>
#include <exception/Exception.h>

namespace zephyr { namespace core {
  
Workshop::Workshop() : m_workshopPremises_p(std::make_unique<Workshop::WorkshopPremises>())
{}

Workshop::~Workshop() = default;

void Workshop::async_start_work()
{
  m_workshopPremises_p->async_start_work();
}

void Workshop::stop_work()
{
  m_workshopPremises_p->stop_work();
}

void Workshop::add_worker()
{
  m_workshopPremises_p->add_worker();
}

void Workshop::add_worker(zephyr::core::result::code& rc)
{
  try
  {
    m_workshopPremises_p->add_worker();
  }
  catch (const Exception& e)
  {
    rc = static_cast<zephyr::core::result::code>(e.get_exception_code());
  }
}

void Workshop::add_to_work_queue(const std::function<void(void)>& workItem)
{
  m_workshopPremises_p->add_to_work_queue(workItem);
}

void Workshop::add_to_work_queue(std::function<void(void)> &&workItem)
{
  m_workshopPremises_p->add_to_work_queue(std::move(workItem));
}
  
size_t Workshop::get_number_of_workers()
{
  return 0;
}
  
}}