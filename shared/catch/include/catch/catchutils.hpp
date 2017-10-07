#pragma once

#include "catch.hpp"

//! Compares 2 std::vectors
template <typename T>
bool compareVectors(const std::vector<T>& vec1, const std::vector<T>& vec2)
{
	if (vec1.size() != vec2.size())
	{
		return false;
	}
	if (vec1.empty())
	{
		return true;
	}
	for (int i = 0; i < vec1.size(); ++i)
	{
		if (vec1[i] != vec2[i])
		{
			return false;
		}
	}
	return true;
}