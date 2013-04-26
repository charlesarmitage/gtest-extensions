// Copyright C.Armitage 2013
// Distributed under the FreeBSD license.
// See accompanying file License.txt
#pragma once
#include "gtest\gtest.h"
#include "StringErrorFormat.h"

inline ::testing::AssertionResult AreStringsEqual(const char* expected_expr, const char* actual_expr, const std::string& expected, const std::string& actual)
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

#define ASSERT_STRINGS_EQUAL(expected, actual) do { \
	ASSERT_PRED_FORMAT2(AreStringsEqual, expected, actual); \
	} while(false)
