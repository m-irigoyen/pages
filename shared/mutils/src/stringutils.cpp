#include <mutils/stringutils.hpp>

#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>


template<typename Out>
void split_verbose(const std::string &s, char delim, Out result) {
    std::stringstream ss (s);
    std::string item;
    while (std::getline(ss, item, delim)) {
    	if (!item.empty())
    	{
    		*(result++) = item;
    	}
    }
}

bool mutils::caseInsensitiveComparisonPredicate(unsigned char a, unsigned char b)
{
	return std::tolower(a) == std::tolower(b);
}

std::vector<std::string> mutils::split(const std::string& s, char delim)
{
	std::vector<std::string> elems;
    split_verbose(s, delim, std::back_inserter(elems));
    return elems;
}

bool mutils::safeCastToInt(const std::string & str, int & result)
{
	try
	{
		result = std::stoi(str);
		return true;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	MUTILS_UNREACHABLE;
	return false;
}

bool mutils::isNumber(const unsigned char c)
{
	return std::isdigit(c) != 0;
}

bool mutils::isNumber(const std::string & s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
	{
		++it;
	}
	return !s.empty() && it == s.end();
}

std::string& mutils::lowercased(std::string& s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		// static_cast<int(*)(int)>(std::tolower)         // wrong
		// [](int c){ return std::tolower(c); }           // wrong
		// [](char c){ return std::tolower(c); }          // wrong
		[](unsigned char c) { return std::tolower(c); } // correct
	);
	return s;
}


std::string mutils::toLowercase(const std::string& str)
{
	std::string s = str;
	return lowercased(s);
}

std::string& mutils::uppercased(std::string& s)
{
	std::transform(s.begin(), s.end(), s.begin(),
		// static_cast<int(*)(int)>(std::tolower)         // wrong
		// [](int c){ return std::tolower(c); }           // wrong
		// [](char c){ return std::tolower(c); }          // wrong
		[](unsigned char c) { return std::toupper(c); } // correct
	);
	return s;
}

std::string mutils::toUppercase(const std::string& str)
{
	std::string s = str;
	return uppercased(s);
}

