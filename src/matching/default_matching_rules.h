#pragma once

#include "AssertionType.pb.h"

namespace zephyr { namespace matching {

struct DefaultMatchingRules
{};

template<AssertionType, typename RuleSet = DefaultMatchingRules>
struct MatchingRule;

template<>
struct MatchingRule<EQUALS, DefaultMatchingRules>
{
  template<typename T>
  static inline bool matches(const T &first, const T &second)
  { return first == second; }
};

template<>
struct MatchingRule<NOT, DefaultMatchingRules>
{
  template<typename T>
  static inline bool matches(const T &first, const T &second)
  { return first != second; }
};

template<>
struct MatchingRule<GREATER_THAN, DefaultMatchingRules>
{
  template<typename T>
  static inline bool matches(const T &first, const T &second)
  { return first > second; }
};

template<>
struct MatchingRule<GREATER_THAN_OR_EQUAL, DefaultMatchingRules>
{
  template<typename T>
  static inline bool matches(const T &first, const T &second)
  { return first >= second; }
};

template<>
struct MatchingRule<LESS_THAN, DefaultMatchingRules>
{
  template<typename T>
  static inline bool matches(const T &first, const T &second)
  { return first < second; }
};

template<>
struct MatchingRule<LESS_THAN_OR_EQUAL, DefaultMatchingRules>
{
  template<typename T>
  static inline bool matches(const T &first, const T &second)
  { return first <= second; }
};

template<>
struct MatchingRule<ANY, DefaultMatchingRules>
{
  template<typename T>
  static constexpr bool matches(const T &first, const T &second)
  { return true; }
};

// If you would like to overload for specific cases the following definition within the correct namespace will work
//
// template <>
// bool MatchingRule<EQUALS>::matches(const std::string& first, const std::string& second) { std::cout << "overload\n"; return first == second; }
//
// You can replace the <EQUALS> with any of the MatchTypes and specify whatever case you want to overload using the function arguments.
// e.g. If you wanted to use your own equality MatchingRule for a class of MyType:
// template <>
// bool MatchingRule<EQUALS>::matches(const MyType& first, const MyType& second) { return first == second; }

// Alternatively you can specify your own MatchingRules using the macros in matching_rule_helpers.h

}}