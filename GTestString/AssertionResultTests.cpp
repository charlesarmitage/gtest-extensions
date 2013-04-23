#include "gtest\gtest.h"

::testing::AssertionResult AreStringsEqual(const std::string& lhs, const std::string& rhs)
{
  if (lhs == rhs)
    return ::testing::AssertionSuccess();
  else
    return ::testing::AssertionFailure(); //<< n << " is odd"; // TODO: This is where error messages can be streamed into the failure.
}

::testing::AssertionResult AreStringsEqualPred(const char* lhs_expr, const char* rhs_expr, const std::string& lhs, const std::string& rhs)
{
	return AreStringsEqual(lhs, rhs);
}

TEST(AssertionResultsTests, UsePredicateFormatAssert)
{
	ASSERT_PRED_FORMAT2(AreStringsEqualPred, "test string", "test string");
}

TEST(AssertionResultTests, EqualStringsShouldReturnSuccessResult)
{
	auto result = AreStringsEqual("test string", "test string");
	ASSERT_EQ(::testing::AssertionSuccess(), result);
}

TEST(AssertionResultTests, DifferentStringsShouldReturnFailureResult)
{
	auto result = AreStringsEqual("test string", "a different string");
	ASSERT_EQ(::testing::AssertionFailure(), result);
}
