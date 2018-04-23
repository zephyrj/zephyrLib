#include <Workshop.h>
#include <impl/workshop/ParentsGarage.h>

namespace zephyr { namespace core {
  
Workshop::Workshop() : m_workshopPremises_p(std::make_unique<Workshop::WorkshopPremises>())
{}

Workshop::~Workshop() = default;

void Workshop::add_worker()
{
  m_workshopPremises_p->add_worker();
}

void Workshop::add_to_work_queue()
{
  
}
  
size_t Workshop::get_number_of_workers()
{
  return 0;
}
  
}}