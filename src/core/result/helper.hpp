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

template <>
struct helper<result::NO_ACTIVE_WORKERS>
{
  static constexpr const char *get_error_string()
  {
    return "No active workers";
  }
};

template <>
struct helper<result::ALREADY_IN_PROGRESS>
{
  static constexpr const char *get_error_string()
  {
    return "Already in-progress";
  }
};

template <>
struct helper<result::NOT_IN_PROGRESS>
{
  static constexpr const char *get_error_string()
  {
    return "Not in-progress";
  }
};



}}}