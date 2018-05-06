#include <Schema.h>

#include <impl/schema/GraphImpl.h>

namespace zephyr { namespace psych {

Schema::Schema() : m_schemaImpl_p(std::make_unique<Schema::SchemaImpl>())
{}

Schema::~Schema() = default;

}}