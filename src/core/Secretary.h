#pragma once

#include <memory>

class Secretary
{
public:
  Secretary();
  ~Secretary();
  
private:
  class Aaron;
  using AppointedSecretary = Aaron;
  
  std::unique_ptr<AppointedSecretary> appointedSecretary_p;
  
};