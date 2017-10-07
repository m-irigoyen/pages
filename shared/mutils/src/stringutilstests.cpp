#include <catch/catch.hpp>

#include <mutils/stringutils.hpp>

using namespace mutils;

namespace
{
	std::string s(const std::string str)
	{
		return std::string(str);
	}
}

TEST_CASE("strings can be compared", "[string]")
{

	SECTION("Basic tests")
	{
		REQUIRE(compare("test", "test") == true);
		REQUIRE(compare("test", "TEST") == false);
		REQUIRE(compare("test", "TEST", false) == true);
		REQUIRE(compare("abcd", "bcde") == false);
		REQUIRE(compare("AbCdE", "aBcDe") == false);
		REQUIRE(compare("AbCdE", "aBcDe", false) == true);
	}

	SECTION("Enriched text")
	{
		REQUIRE(compare("é", "é") == true);
		REQUIRE(compare("ê", "é") == false);
		REQUIRE(compare("a", "à") == false);
	}

	SECTION("Spaces should be properly compared")
	{
		REQUIRE(compare(std::string("abcd "), std::string("abcd")) == false);
		REQUIRE(compare(std::string(" abcd "), std::string("abcd")) == false);
		REQUIRE(compare(std::string(" abcd"), std::string("abcd")) == false);
		REQUIRE(compare(std::string("       abcd"), std::string("abcd")) == false);
		REQUIRE(compare(std::string("       abcd         "), std::string("abcd")) == false);
		REQUIRE(compare(std::string("abcd         "), std::string("abcd")) == false);
		REQUIRE(compare(std::string("abcd "), std::string("abcd ")) == true);
		REQUIRE(compare(std::string(" abcd "), std::string(" abcd ")) == true);
		REQUIRE(compare(std::string(" abcd"), std::string(" abcd")) == true);
	}
}

TEST_CASE("strings can be trimmed", "[string]")
{
	std::string test1 = "ceci est un test";
	std::string test2 = "Ceci Est uN AuTre teSt";


	SECTION("Trim does not remove unnecessary spaces")
	{
		REQUIRE(compare(trimLeft(test1), test1) == true);
		REQUIRE(compare(trimLeft(test2), test2) == true);

		REQUIRE(compare(trimLeft(test1), test1) == true);
		REQUIRE(compare(trimLeft(test2), test2) == true);

		REQUIRE(compare(trimLeft(test1), test1) == true);
		REQUIRE(compare(trimLeft(test2), test2) == true);
	}

	SECTION("General trimming")
	{
		REQUIRE(compare(trimLeft(s("T")), s("T")) == true);
		REQUIRE(compare(trimLeft(s("T ")), s("T ")) == true);
		REQUIRE(compare(trimLeft(s(" T ")), s("T ")) == true);
		REQUIRE(compare(trimLeft(s(" T")), s("T")) == true);

		REQUIRE(compare(trimRight(s("T")), s("T")) == true);
		REQUIRE(compare(trimRight(s("T ")), s("T")) == true);
		REQUIRE(compare(trimRight(s(" T ")), s(" T")) == true);
		REQUIRE(compare(trimRight(s(" T")), s(" T")) == true);

		REQUIRE(compare(trim(s("T")), s("T")) == true);
		REQUIRE(compare(trim(s("T ")), s("T")) == true);
		REQUIRE(compare(trim(s(" T ")), s("T")) == true);
		REQUIRE(compare(trim(s(" T")), s("T")) == true);
	}

	SECTION("Many spaces")
	{
		REQUIRE(compare(trimLeft(s("     T ")), s("T ")) == true);
		REQUIRE(compare(trimLeft(s("     T")), s("T")) == true);

		REQUIRE(compare(trimRight(s("T     ")), s("T")) == true);
		REQUIRE(compare(trimRight(s(" T        ")), s(" T")) == true);

		REQUIRE(compare(trim(s(" T    ")), s("T")) == true);
		REQUIRE(compare(trim(s("       T ")), s("T")) == true);
		REQUIRE(compare(trim(s("       T       ")), s("T")) == true);
	}
}