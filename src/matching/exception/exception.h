#pragma once

#include <stdexcept>

namespace zephyr { namespace matching {

class Exception : public std::runtime_error
{
public:
  Exception(const std::string &error) : std::runtime_error("Query error: " + error)
  {};
};

namespace exception {
class EmptyQuery final : public Exception
{
public:
  EmptyQuery() : Exception("Empty Query")
  {};
};

class InvalidQuery final : public Exception
{
public:
  InvalidQuery(const std::string &error) : Exception("Query invalid: " + error)
  {};
};
}

}}
