// Copyright C.Armitage 2013
// Distributed under the FreeBSD license.
// See accompanying file License.txt
#include "gtest\gtest.h"
#include "DetailedStringAsserts.h"

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
