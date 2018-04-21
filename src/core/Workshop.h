#pragma once

#include <memory>

class Workshop
{
public:
  Workshop();
  ~Workshop();
  
  void add_worker();
  void add_to_work_queue();
  
  size_t get_number_of_workers();
  
private:
  class ParentsGarage;
  using WorkshopPremises = ParentsGarage;
  
  std::unique_ptr<WorkshopPremises> m_workshopPremises_p;
  
};