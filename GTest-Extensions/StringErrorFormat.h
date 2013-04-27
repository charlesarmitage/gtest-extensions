// Copyright C.Armitage 2013
// Distributed under the FreeBSD license.
// See accompanying file License.txt

#pragma once
#include <iostream>
#include <string>
#include <algorithm>

std::string create_msg(const std::string& match)
{
	std::stringstream message;
	message << "Expected and actual differ at index: " << match.length() << ".\n";
	message << "Matching section:\n";
	message << "'" << match << "'\n";
	return message.str();
}

std::string format_error_msg(const std::string& expected, const std::string& actual)
{
	if(expected == actual)
	{
		return "No error. Strings are identical.";
	}
	else if(expected.length() > actual.length())
	{
		return create_msg(actual);
	}

	auto result = std::mismatch(expected.begin(), expected.end(), actual.begin());
	auto expected_position = result.first;
	auto actual_position = result.second;
	
	std::string match;
	if(expected_position != expected.end())
	{
		match = std::string(expected.begin(), expected_position);
	}
	else if(actual_position != actual.end())
	{
		match = expected;
	}

	return create_msg(match);
}
