#pragma once

namespace zephyr { namespace core { namespace result {

using code_type = int;

enum code : code_type {
  SUCCESS = 0,
  UNSPECIFIED_ERROR = 1,
  MAX_WORKER_LIMIT_REACHED = 2,
  NO_ACTIVE_WORKERS = 3,
  ALREADY_IN_PROGRESS = 4,
  NOT_IN_PROGRESS = 5
};

}}}