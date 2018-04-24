#pragma once

#include "codes.h"

namespace zephyr { namespace core { namespace result {

template <code>
struct helper
{
  static constexpr const char* get_error_string()
  {
    return "Unspecified result";
  }
};

template <>
struct helper<result::SUCCESS>
{
  static constexpr const char *get_error_string()
  {
    return "Success";
  }
};

template <>
struct helper<result::UNSPECIFIED_ERROR>
{
  static constexpr const char *get_error_string()
  {
    return "Unspecified error";
  }
};

template <>
struct helper<result::MAX_WORKER_LIMIT_REACHED>
{
  static constexpr const char *get_error_string()
  {
    return "Max worker limit reached";
  }
};

}}}