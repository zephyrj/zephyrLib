#pragma once

namespace zephyr { namespace matching {

template <typename TypeToApplyTo>
class Assertion
{
public:
  virtual ~Assertion() = default;

  virtual bool applyTo(const TypeToApplyTo& filterSubject) const = 0;

};

}}