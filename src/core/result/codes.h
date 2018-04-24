#pragma once

namespace zephyr { namespace core { namespace result {

using code_type = int;

enum code : code_type {
  SUCCESS = 0,
  UNSPECIFIED_ERROR = 1,
  MAX_WORKER_LIMIT_REACHED = 2
};

}}}