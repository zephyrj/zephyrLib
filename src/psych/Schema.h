#pragma once

#include <memory>

namespace zephyr { namespace psych {

class Schema final
{
public:
  Schema();
  ~Schema();

private:
  class GraphImpl;
  using SchemaImpl = GraphImpl;

  std::unique_ptr<SchemaImpl> m_schemaImpl_p;

};

}}

