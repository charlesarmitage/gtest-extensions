#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "StringErrorFormat.h"

SCENARIO( "Display mis-matching strings" )
{
	GIVEN( "An expected string" )
	{
		std::string expected = "This is the expected string.";
		
		WHEN( "Actual differs at first character" )
		{
			auto actual = "A completely different string";

			auto error_msg = format_error_msg(expected, actual);
			REQUIRE( error_msg == "Expected and actual differ at index: 0.\n\
Matching section:\n\
\'\'\n");
		}

		WHEN( "Actual differs at ninth character" )
		{
			auto actual = "This is an unexpected string";

			auto error_msg = format_error_msg(expected, actual);

			REQUIRE( error_msg == "Expected and actual differ at index: 8.\n\
Matching section:\n\
\'This is \'\n");
		}

		WHEN( "Actual is shorter than expected string" )
		{
			auto actual = "This is the expected";

			auto msg = format_error_msg(expected, actual);

			REQUIRE( msg == "Expected and actual differ at index: 20.\n\
Matching section:\n\
\'This is the expected\'\n");
		}

		WHEN( "Actual is longer than expected string" )
		{
			auto actual = "This is the expected string. But this is not.";

			auto error_msg = format_error_msg(expected, actual);

			REQUIRE( error_msg == "Expected and actual differ at index: 28.\n\
Matching section:\n\
\'This is the expected string.\'\n");
		}

		WHEN( "Actual string is empty" )
		{
			auto actual = "";

			auto error_msg = format_error_msg(expected, actual);

			REQUIRE( error_msg == "Expected and actual differ at index: 0.\n\
Matching section:\n\
\''\n");
		}

		WHEN( "Expected string is empty" )
		{
			auto actual = "This is the expected string.";
			auto expected = "";

			auto error_msg = format_error_msg(expected, actual);

			REQUIRE( error_msg == "Expected and actual differ at index: 0.\n\
Matching section:\n\
\''\n");
		}

		WHEN( "Strings are identical" )
		{
			auto actual = "This is the expected string.";

			auto error_msg = format_error_msg(expected, actual);

			REQUIRE( error_msg == "No error. Strings are identical." );
		}
	}
}
