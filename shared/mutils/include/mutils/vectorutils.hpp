#pragma once

#include <vector>
#include <algorithm>

namespace mutils
{
	//! In given vector, adds given value only if it doesn't already exist
	template <typename T>
	bool addUnique(std::vector<T>& vector, const T& value)
	{
		if (find(vector.begin(), vector.end(), value) == vector.end())
		{
			vector.push_back(value);
			return true;
		}
		else
		{
			return false;
		}
	}

	//TODO : case insensitive contains version
	template <typename T>
	bool contains(const std::vector<T>& vector, const T& value)
	{
		return (std::find(vector.begin(), vector.end(), value) != vector.end());
	}


	//! In given vector, erase element at position vec[index]
	template <typename T>
	bool eraseAt(std::vector<T>& vector, unsigned int index)
	{
		if (index >= 0 && index < vector.size())
		{
			vector.erase(vector.begin() + index);
			return true;
		}
		return false;
	}

	//! In given vector, erase element at position vec[index]
	template <typename T>
	bool eraseAll(std::vector<T>& vector, const T& value)
	{
		bool erasedSomething = false;
		typename std::vector<T>::iterator it = vector.begin();
		while (it != vector.end())
		{
			if (*it == value)
			{
				it = vector.erase(it);
				erasedSomething = true;
			}
			else
			{
				++it;
			}
		}
		return erasedSomething;
	}

	//! In given vector, erase given value once
	template <typename T>
	bool eraseOne(std::vector<T>& vector, const T& value)
	{
		typename std::vector<T>::iterator it = std::find(
			vector.begin()
			, vector.end()
			, value);
		if (it != vector.end())
		{
			vector.erase(it);
			return true;
		}
		return false;
	}

	template <typename T>
	bool find(const std::vector<T>& vector, const T& value)
	{
		return (std::find(vector.begin(), vector.end(), value) != vector.end());
	}

	//! In given vector, element at pos vec[src] will be moved at pos vec[dst]
	/* Examples:
	* [0,1,2,3,4] -> move(1,3) -> [0,2,3,1,4]
	* [0,1,2,3,4] -> move(2,0) -> [2,0,1,3,4]
	* Returns false if src == dst, or if src or dst are invalid
	*/
	template <typename T>
	bool move(std::vector<T>& vector, unsigned int src, unsigned int dst)
	{
		if ((src >= 0 && src < vector.size())
			&& (dst >= 0 && dst < vector.size())
			&& (src != dst))
		{
			T tmp = vector[src];
			vector.erase(vector.begin() + src);
			vector.insert(vector.begin() + dst, tmp);
			return true;
		}
		return false;
	}

	//! In given vector, element at pos vec[src] and vec[dst] are swapped
	/* Examples:
	* [0,1,2,3,4] -> swap(2,1) -> [0,2,1,3,4]
	*/
	template <typename T>
	bool swap(std::vector<T>& vector, unsigned int src, unsigned int dst)
	{
		if ((src >= 0 && src < vector.size())
			&& (dst >= 0 && dst < vector.size())
			&& (src != dst))
		{
			T tmp = vector[src];
			vector[src] = vector[dst];
			vector[dst] = tmp;
			return true;
		}
		return false;
	}
}