#include <Workshop.h>

class Workshop::ParentsGarage
{
public:
  ParentsGarage()
  {}
  
  ~ParentsGarage() = default;
  
};

Workshop::Workshop() : m_workshopPremises_p(std::make_unique<ParentsGarage>())
{}

Workshop::~Workshop() = default;

void Workshop::add_worker()
{
  
}

void Workshop::add_to_work_queue()
{
  
}
  
size_t get_number_of_workers()
{
  return 0;
}
