#include "gtest\gtest.h"

#include "StringErrorFormat.h"

::testing::AssertionResult AreStringsEqual(const char* expected_expr, const char* actual_expr, const std::string& expected, const std::string& actual)
{
  if (expected == actual)
    return ::testing::AssertionSuccess();
  
  auto failure_msg = ::testing::AssertionFailure();

  failure_msg << "'" << expected_expr << "' & " << "'" << actual_expr << "' are not equal.\n";
  failure_msg << "Expected: " << expected << '\n';
  failure_msg << "Actual:   " << actual << '\n';
  failure_msg << format_error_msg(expected, actual);

  return failure_msg;
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

TEST(AssertionResultTests, DifferentStringsShouldReturnDetailedErrorMessage)
{
	auto expected_str = "a test string";
	auto actual_str = "a different string";
	auto result = AreStringsEqual("expected_str", "actual_str", expected_str, actual_str);

	ASSERT_STREQ("'expected_str' & 'actual_str' are not equal.\n\
Expected: a test string\n\
Actual:   a different string\n\
Expected and actual differ at index: 2.\n\
Matching section:\n\
'a '\n",
result.message());
}
