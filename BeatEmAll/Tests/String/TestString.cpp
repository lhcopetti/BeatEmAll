
#include "Catch\catch.hpp"

#include "String\SplitString.h"

TEST_CASE("Splitting a String", "[string]")
{
	{
		std::string content = "Teste1|abc|remoto";
		std::vector<std::string> output;
		String::split(content, '|', output);

		REQUIRE(output.size() == 3);
		CHECK(output[0] == "Teste1");
		CHECK(output[1] == "abc");
		CHECK(output[2] == "remoto");
	}

	std::string content = "animal";
	std::vector<std::string> output;
	String::split(content, '|', output);

	REQUIRE(output.size() == 1);
	CHECK(output[0] == "animal");
}