#pragma once

#include <memory>

namespace zephyr { namespace core {

class Secretary
{
public:
  Secretary();
  ~Secretary();
  
private:
  class Aaron;
  using AppointedSecretary = Aaron;
  
  std::unique_ptr<AppointedSecretary> m_appointedSecretary_p;
  
};
    
}}
