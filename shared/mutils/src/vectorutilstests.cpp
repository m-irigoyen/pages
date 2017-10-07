#pragma once

#include <mutils/vectorutils.hpp>

#include <catch/catch.hpp>
#include <catch/catchutils.hpp>

using namespace mutils;

TEST_CASE("'contains' tests", "[vectorutils]")
{
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(-17);
	REQUIRE(contains(vec, 1));
	REQUIRE(contains(vec, 3));
	REQUIRE(contains(vec, 5));
	REQUIRE(contains(vec, -17));
	REQUIRE(!contains(vec, -12));
	REQUIRE(!contains(vec, 17));
	REQUIRE(!contains(vec, 2));
}

TEST_CASE("'eraseAt' tests", "[vectorutils]")
{
	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);

	SECTION("Correctly erases first element")
	{
		std::vector<int> expected(vec.begin() + 1, vec.end());
		REQUIRE(eraseAt(vec, 0));
		REQUIRE(compareVectors(vec, expected));
	}

	SECTION("Correctly erases last element")
	{
		std::vector<int> expected(vec.begin(), vec.end()-1);
		REQUIRE(eraseAt(vec, 5));
		REQUIRE(compareVectors(vec, expected));
	}

	SECTION("Correctly erases middle element")
	{
		std::vector<int> expected(vec);
		expected.erase(std::find(expected.begin(), expected.end(), 3));
		REQUIRE(eraseAt(vec, 3));
		REQUIRE(compareVectors(vec, expected));
	}

	SECTION("Returns false when index is incorrect")
	{
		REQUIRE(!eraseAt(vec, -1));
		REQUIRE(!eraseAt(vec, 6));
		REQUIRE(!eraseAt(vec, 150));
	}
}

TEST_CASE("'eraseAll' tests", "[vectorutils]")
{
	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(2);
	vec.push_back(3);

	SECTION("Correctly erases first element")
	{
		std::vector<int> expected(vec.begin() + 1, vec.end());
		REQUIRE(eraseAll(vec, 0));
		REQUIRE(compareVectors(vec, expected));
	}

	SECTION("Correctly erases last element")
	{
		std::vector<int> expected(vec.begin(), vec.end() - 1);
		REQUIRE(eraseAll(vec, 3));
		REQUIRE(compareVectors(vec, expected));
	}

	SECTION("Correctly erases middle elements")
	{
		std::vector<int> expected(vec);
		expected.erase(std::find(expected.begin(), expected.end(), 2));
		expected.erase(std::find(expected.begin(), expected.end(), 2));
		REQUIRE(eraseAll(vec, 2));
		REQUIRE(compareVectors(vec, expected));
	}

	SECTION("Returns false if nothing was erased")
	{
		REQUIRE(!eraseAll(vec, -1));
	}
}

TEST_CASE("'addUnique' tests", "[vectorutils]")
{
	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);

	SECTION("Correctly adds element")
	{
		std::vector<int> expected(vec);
		expected.push_back(-1);
		REQUIRE(addUnique(vec, -1));
		REQUIRE(compareVectors(vec, expected));
	}

	SECTION("Doesn't add if already exists")
	{
		REQUIRE(!addUnique(vec, 1));
	}
}

TEST_CASE("'move' tests", "[vectorutils]")
{
	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	SECTION("Correctly moves to bigger destination")
	{
		std::vector<int> expected{0, 2, 3, 1, 4};
		REQUIRE(move(vec, 1,3));
		REQUIRE(compareVectors(vec, expected));
	}
	SECTION("Correctly moves to lower destination")
	{
		std::vector<int> expected{ 2, 0, 1, 3, 4 };
		REQUIRE(move(vec, 2, 0));
		REQUIRE(compareVectors(vec, expected));
	}
	SECTION("False if src == dst")
	{
		REQUIRE(!move(vec, 2, 2));
	}
	SECTION("False if src or dst is invalid")
	{
		REQUIRE(!move(vec, -1, 2));
		REQUIRE(!move(vec, 10, 2));
		REQUIRE(!move(vec, 2, -2));
		REQUIRE(!move(vec, 2, 7));
	}
}

TEST_CASE("'swap' tests", "[vectorutils]")
{
	std::vector<int> vec;
	vec.push_back(0);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);

	SECTION("Correctly swaps to bigger destination")
	{
		std::vector<int> expected{ 0, 3, 2, 1, 4 };
		REQUIRE(swap(vec, 1, 3));
		REQUIRE(compareVectors(vec, expected));
	}
	SECTION("Correctly swaps to lower destination")
	{
		std::vector<int> expected{ 2, 1, 0, 3, 4 };
		REQUIRE(swap(vec, 2, 0));
		REQUIRE(compareVectors(vec, expected));
	}
	SECTION("False if src == dst")
	{
		REQUIRE(!swap(vec, 2, 2));
	}
	SECTION("False if src or dst is invalid")
	{
		REQUIRE(!swap(vec, -1, 2));
		REQUIRE(!swap(vec, 10, 2));
		REQUIRE(!swap(vec, 2, -2));
		REQUIRE(!swap(vec, 2, 7));
	}
}
