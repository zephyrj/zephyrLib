#include <Director.h>
#include <impl/director/Amy.h>

namespace zephyr { namespace core {
  
Director::Director() : m_appointedDirector_p(std::make_unique<Director::AppointedDirector>())
{}

Director::~Director() = default; 

}}