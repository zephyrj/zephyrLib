#pragma once

#include <memory>

namespace zephyr { namespace core {
  
class Director
{
public:
  Director();
  ~Director();
  
private:
  class Amy;
  using AppointedDirector = Amy;
  
  std::unique_ptr<AppointedDirector> m_appointedDirector_p;
  
};
  
}}