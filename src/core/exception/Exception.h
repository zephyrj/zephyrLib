#pragma once

#include <stdexcept>

#include <result/codes.h>
#include <result/helper.hpp>

namespace zephyr { namespace core {

class Exception : public std::runtime_error
{
public:
  template <result::code rc>
  static inline void throw_exception()
  {
    throw Exception(rc, result::helper<rc>::get_error_string());
  }

  explicit Exception(result::code_type exception_code, const char* exception_string);

  const result::code_type get_exception_code() const;
  const char* get_exception_string() const;

private:
  const result::code_type m_exception_code;

};

}}

