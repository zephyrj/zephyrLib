#include "Component.hpp"
#include "Framework.hpp"

namespace zephyr { namespace async { namespace framework {

std::atomic<long> Component::NEXT_COMPONENT_ID(1);

Component::Component(Framework &framework, const std::string &componentName)
    : framework(framework),
      id(NEXT_COMPONENT_ID.fetch_add(1, std::memory_order_release)),
      name(componentName+std::to_string(id))
{
  framework.componentAdded(this);
}

Component::~Component()
{
  framework.componentRemoved(this);
}

long Component::getId() const
{
  return id;
}

const std::string Component::getName() const
{
  return name;
}

void Component::setName(const std::string &newName)
{
  name = newName;
}

}}}