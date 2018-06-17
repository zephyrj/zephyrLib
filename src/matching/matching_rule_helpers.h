#pragma once
// Helper macros for creating matching rules.
//
// These must be used with the namespace zephyr::matching to allow the template
// specializations/overloads to work.
//
// It is recommended that you:
// - create your own file
// - declare the zephyr::matching namespace at the top
//   i.e. namespace zephyr { namespace matching {
// - use the below macros to create your rule set within the namespace
// - you must declare a rule for every assertion type that will be used
//   if you don't want to declare a custom rule for every assertion type
//   then you can use the USE_DEFAULT_RULE to use the default for a given
//   assertion type

#define CREATE_MATCHING_RULE_SET(RuleSetClassName) \
struct RuleSetClassName {};

#define USE_DEFAULT_RULE(AssertionType, MatchingRuleSet) \
template <> \
struct MatchingRule<AssertionType, MatchingRuleSet> \
{ \
  template <typename T> \
  static bool matches(const T& first, const T& second) \
  { \
    return MatchingRule<AssertionType, zephyr::matching::DefaultMatchingRules>::template matches(first, second); \
  } \
};

// Where Rule is an expression that has access to the first and second values to match and returns a boolean value
#define ADD_MATCHING_RULE(AssertionType, MatchingRuleSet, Rule) \
template <> \
struct MatchingRule<AssertionType, MatchingRuleSet> \
{ \
  template <typename T> \
  static bool matches(const T& first, const T& second) \
  { \
    return Rule; \
  } \
};

// NOTE: These specializations can't be made within the struct body because of a defect in C++11
//       See the following for more details: http://open-std.org/JTC1/SC22/WG21/docs/cwg_defects.html#727
#define ADD_MATCHING_RULE_TYPE_SPECIALIZATION(AssertionType, MatchingRuleSet, TypeToSpecialize,  Rule) \
template <> \
bool MatchingRule<AssertionType, MatchingRuleSet>::matches(const TypeToSpecialize& first, const TypeToSpecialize& second) { return RULE; }
