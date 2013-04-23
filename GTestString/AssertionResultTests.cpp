#include "gtest\gtest.h"

#include "StringErrorFormat.h"

::testing::AssertionResult AreStringsEqual(const char* lhs_expected, const char* rhs_actual, const std::string& expected, const std::string& actual)
{
  if (expected == actual)
    return ::testing::AssertionSuccess();
  else
    return ::testing::AssertionFailure(); //<< n << " is odd"; // TODO: This is where error messages can be streamed into the failure.
}

#define ASSERT_STRINGS_EQUAL(expected, actual) do{ ASSERT_PRED_FORMAT2(AreStringsEqual, expected, actual); }while(false)

TEST(AssertionResultsTests, UsePredicateFormatAssert)
{
	ASSERT_PRED_FORMAT2(AreStringsEqual, "test string", "test string");
}

TEST(AssertionResultsTests, UseCustomAssertMacro)
{
	ASSERT_STRINGS_EQUAL("test string", "test string");
}

TEST(AssertionResultTests, EqualStringsShouldReturnSuccessResult)
{
	auto expected_str = "test string";
	auto actual_str = "test string";
	auto result = AreStringsEqual("expected_str", "actual_str", expected_str, actual_str);
	ASSERT_EQ(::testing::AssertionSuccess(), result);
}

TEST(AssertionResultTests, DifferentStringsShouldReturnFailureResult)
{
	auto expected_str = "test string";
	auto actual_str = "a different string";
	auto result = AreStringsEqual("expected_str", "actual_str", expected_str, actual_str);
	ASSERT_EQ(::testing::AssertionFailure(), result);
}
