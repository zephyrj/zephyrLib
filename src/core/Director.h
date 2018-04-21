#pragma once

#include <memory>

class Director
{
public:
  Director();
  ~Director();
  
private:
  class Amy;
  using AppointedDirector = Amy;
  
  std::unique_ptr<AppointedDirector> appointedDirector_p;
  
};