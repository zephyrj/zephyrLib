#include "catch.hpp"

#include <ScopedCallbackHelper.hpp>

void func(int& x)
{
  x++;
}

SCENARIO("ScopedCallback tests with std::bind")
{
  GIVEN("A callback helper")
  {
    auto callbackHelper = std::make_unique<zephyr::async::ScopedCallbackHelper>();

    WHEN("We create a callback using std::bind and bound arguments with the callback helper")
    {
      int testInt = 0;
      auto callback = callbackHelper->createCallback(std::bind(&func, std::ref(testInt)));

      THEN("The callback should execute as expected when the helper is in scope")
      {
        callback();
        CHECK(testInt == 1);

        AND_THEN("The callback shouldn't execute when the helper goes out of scope")
        {
          callbackHelper.reset(nullptr);
          callback();
          CHECK(testInt == 1);
        }
      }
    }

    WHEN("We create a callback using std::bind and std::placeholder with the callback helper")
    {
      auto callback = callbackHelper->createCallback(std::bind(&func, std::placeholders::_1));

      THEN("The callback should execute as expected")
      {
        int testInt = 0;
        callback(testInt);
        CHECK(testInt == 1);

        AND_THEN("The callback shouldn't execute when the helper goes out of scope")
        {
          callbackHelper.reset(nullptr);
          callback(testInt);
          CHECK(testInt == 1);
        }
      }
    }
  }
}

SCENARIO("ScopedCallback tests with lambdas")
{
  GIVEN("A callback helper")
  {
    auto callbackHelper = std::make_unique<zephyr::async::ScopedCallbackHelper>();

    WHEN("We create a callback using a simple lambda with captured arguments with the callback helper")
    {
      int testInt = 0;
      auto callback = callbackHelper->createCallback([&testInt](){ testInt++; });

      THEN("The callback should execute as expected when the helper is in scope")
      {
        callback();
        CHECK(testInt == 1);

        AND_THEN("The callback shouldn't execute when the helper goes out of scope")
        {
          callbackHelper.reset(nullptr);
          callback();
          CHECK(testInt == 1);
        }
      }
    }

    WHEN("We create a callback using lambda that takes arguments with the callback helper")
    {
      auto callback = callbackHelper->createCallback([](int& intToIncrement, const int& intToLeaveAlone)
                                                     {
                                                       intToIncrement++;
                                                     });

      THEN("The callback should execute as expected")
      {
        int testInt = 0;
        const int controlInt = 0;

        callback(testInt, controlInt);
        CHECK(testInt == 1);
        CHECK(controlInt == 0);

        AND_THEN("The callback shouldn't execute when the helper goes out of scope")
        {
          callbackHelper.reset(nullptr);
          callback(testInt, controlInt);
          CHECK(testInt == 1);
          CHECK(controlInt == 0);
        }
      }
    }
  }
}

