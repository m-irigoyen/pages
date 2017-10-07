#include <catch/catch.hpp>

#include <mutils/collision.hpp>

using namespace mutils;

std::string s(const std::string str)
{
	return std::string(str);
}

TEST_CASE("isInAABB tests", "[collision]")
{

	SECTION("Rectangle tests")
	{
		Vec2 p(10, 10);

		REQUIRE(isInAABB(p, 0.f, 0.f, 20.0f, 20.f));
		REQUIRE(isInAABB(p, 0.f, 0.f, 5.0f, 20.f) == false);
		REQUIRE(isInAABB(p, 0.f, 0.f, 20.f, 5.f) == false);
		REQUIRE(isInAABB(p, 5.f, 0.f, 20.f, 20.f));
		REQUIRE(isInAABB(p, 0.f, 5.f, 20.f, 20.f));
	}
}