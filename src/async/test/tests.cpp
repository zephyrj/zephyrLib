#include "catch.hpp"

#include <ScopedCallbackHelper.hpp>

void func()
{
  std::string x;
}

TEST_CASE("Compile please")
{
  zephyr::async::ScopedCallbackHelper x;
  x.createCallback(std::bind(&func));
}

