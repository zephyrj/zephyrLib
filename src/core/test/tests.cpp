#include <Workshop.h>
#include <exception/Exception.h>
#include "catch.hpp"

TEST_CASE("Basic usage")
{
  auto i = 0;
  zephyr::core::Workshop workshop;
  workshop.add_to_work_queue([&i](){ i++; });

  SECTION("Trying to start work with no workers throws an Exception")
  {
    REQUIRE_THROWS_AS(workshop.async_start_work(), zephyr::core::Exception);
  }

  SECTION("Trying to stop work before starting it throws an Exception")
  {
    REQUIRE_THROWS_AS(workshop.stop_work(), zephyr::core::Exception);
  }

  SECTION("Can add a worker and do some work")
  {
    workshop.add_worker();
    workshop.async_start_work();
    SECTION("Trying to start work twice raises an exception")
    {
      REQUIRE_THROWS_AS(workshop.async_start_work(), zephyr::core::Exception);
    }
    workshop.stop_work();
    SECTION("Trying to stop work twice raises and exception")
    {
      REQUIRE_THROWS_AS(workshop.stop_work(), zephyr::core::Exception);
    }
    REQUIRE(i == 1);
  }
}
