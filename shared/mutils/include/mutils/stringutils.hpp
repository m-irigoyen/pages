#pragma once

#include <mutils/assert.hpp>

#include <algorithm>
#include <cctype>
#include <functional>

#include <string>
#include <vector>

namespace mutils
{
	//----------------------------
	// Basic utils
	//----------------------------

	//! Trim string from start (in place)
	//! @param[in,out] s The string to trim
	template <typename T>
	static inline T& trimLeft(T &s)
	{
		// STL pro version
		s.erase(s.begin(), std::find_if(
			s.begin()
			, s.end()
			, std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	//! Trim string from end (in place)
	//! @param[in,out] s The string to trim
	template <typename T>
	static inline T& trimRight(T &s)
	{
		// STL pro version
		s.erase(std::find_if(s.rbegin()
			, s.rend()
			, std::not1(std::ptr_fun<int, int>(std::isspace))
			).base(), s.end());
		return s;
	}

	//! Returns string trimmed from start (copying)
	//! @param[in] s The string to trim
	template <typename T>
	static inline T trimmedLeft(T s) {
		trimLeft(s);
		return s;
	}

	//! Returns string trimmed from end (copying)
	//! @param[in] s The string to trim
	template <typename T>
	static inline T trimmedRight(T s) {
		trimRight(s);
		return s;
	}

	//! Trim string from both ends (in place)
	//! @param[in,out] s The string to trim
	template <typename T>
	static inline T& trim(T &s)
	{
		return trimRight(trimLeft(s));
	}

	//! Returns string trimmed from both ends (copying)
	//! @param[in] s The string to trim
	template <typename T>
	static inline T trimmed(T s) {
		return trim(s);
	}

	//! Returns true if string s contains string searched
	//! @param[in] s The complete string
	//! @param[in] searched The substring to search for
	template <typename T>
	static inline bool contains(T s, T searched)
	{
		return s.find(searched) != T::npos;
	}

	bool caseInsensitiveComparisonPredicate(unsigned char a, unsigned char b);


	//! Returns true if both strings are equal
	//! @param[in] s1 A string to compare
	//! @param[in] s2 A string to compare
	static inline bool compare(const std::string& s1
		, const std::string& s2
		, bool caseSensitive = true)
	{
		if (s1.size() == s2.size())
		{
			if (caseSensitive)
			{
				return s1.compare(s2) == 0;
			}
			else
			{
				return std::equal(s1.begin(), s1.end(),
					s2.begin(), caseInsensitiveComparisonPredicate);
			}
		}
		else
		{
			return false;
		}

		MUTILS_ASSERT("unreachable code");
		return false;
	}

	//! Splits given string between each instance of the "delimiter" char
	//! If no delimiter is found, just return the same string inside a vector
	//! If the string is empty, return an empty vector
	std::vector<std::string> split(const std::string& s, char delimiter);

	//! Calls std::stoi, handling any exceptions thrown. Returns true if the cast was successful,
	// and result contains the result
	bool safeCastToInt(const std::string& str, int& result);

	//! Returns true if c is a number
	bool isNumber(const unsigned char c);
	bool isNumber(const std::string& str);

	std::string toLowercase(const std::string& s);
	std::string& lowercased(std::string& s);
	std::string toUppercase(const std::string& s);
	std::string& uppercased(std::string& s);

}