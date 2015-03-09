// Copyright C.Armitage 2013
// Distributed under the FreeBSD license.
// See accompanying file License.txt

#pragma once
#include <iostream>
#include <string>
#include <algorithm>

inline std::string create_msg(const std::string& match)
{
	std::stringstream message;
	message << "Expected and actual differ at index: " << match.length() << ".\n";
	message << "Matching section:\n";
	message << "'" << match << "'\n";
	return message.str();
}

inline std::string matching_expected_substring(const std::string& expected, const std::string& actual)
{
	auto padded_actual = actual;
	if(expected.length() > actual.length())
	{
		padded_actual.resize(expected.length());
	}

	auto result = std::mismatch(expected.begin(), expected.end(), padded_actual.begin());
	auto expected_position = result.first;
	auto actual_position = result.second;
	
	std::string match;
	if(expected_position != expected.end())
	{
		match = std::string(expected.begin(), expected_position);
	}
	else if(actual_position != padded_actual.end())
	{
		match = expected;
	}

	return create_msg(match);
}

inline std::string format_error_msg(const std::string& expected, const std::string& actual)
{
	if(expected == actual)
	{
		return "No error. Strings are identical.";
	}

	return matching_expected_substring(expected, actual);
}
