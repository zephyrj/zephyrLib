#pragma once

#include <memory>
#include <functional>
#include <result/codes.h>

namespace zephyr { namespace core {

class Workshop
{
public:
  Workshop();
  ~Workshop();

  void async_start_work();

  void stop_work();

  void add_worker();
  void add_worker(zephyr::core::result::code& rc);

  void add_to_work_queue(const std::function<void(void)>& workItem);
  void add_to_work_queue(std::function<void(void)>&& workItem);
  
  size_t get_number_of_workers();
  
private:
  class ParentsGarage;
  using WorkshopPremises = ParentsGarage;
  
  std::unique_ptr<WorkshopPremises> m_workshopPremises_p;
  
};
  
}}