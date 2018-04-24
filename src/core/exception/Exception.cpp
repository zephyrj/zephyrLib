#include "Exception.h"

namespace zephyr { namespace core {

Exception::Exception(result::code_type exception_code, const char* exception_string)
        : std::runtime_error(exception_string),
          m_exception_code(exception_code)
{}

const result::code_type Exception::get_exception_code() const
{
  return m_exception_code;
}

const char *Exception::get_exception_string() const
{
  return what();
}

}}