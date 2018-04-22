#include <Secretary.h>
#include <impl/secretary/Aaron.h>

namespace zephyr { namespace core {
  
Secretary::Secretary() : m_appointedSecretary_p(std::make_unique<Secretary::AppointedSecretary>())
{}

Secretary::~Secretary() = default;
  
}}