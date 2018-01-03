#ifndef ZEPHYR_ASYNC_FRAMEWORK_SCOPEDCOMPONENT_HPP
#define ZEPHYR_ASYNC_FRAMEWORK_SCOPEDCOMPONENT_HPP

#include <memory>
#include <atomic>

namespace zephyr { namespace async {

class Framework;

namespace framework {

class Component : protected std::enable_shared_from_this<Component>
{
  static std::atomic<long> NEXT_COMPONENT_ID;

protected:
  Component(Framework& framework, const std::string& componentName = "component");

public:
  virtual ~Component();

  virtual void shutdown() = 0;

  const std::string getName() const;
  void setName(const std::string& name);

  long getId() const __attribute__ ((pure));

protected:
  Framework& framework;

private:
  const long id;
  std::string name;

};

}}}

#endif
