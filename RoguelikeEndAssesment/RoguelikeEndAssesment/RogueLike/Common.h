#pragma once

#include <sstream>
#include <string>

#define uint unsigned int

namespace RogueLike {

	template<typename T>
	std::string ToString(const T& v)
	{
		std::ostringstream ss;
		ss << v;
		return ss.str();
	}

	template<typename T>
	T FromString(const std::string& str)
	{
		std::istringstream ss(str);
		T ret;
		ss >> ret;
		return ret;
	}
	
	/*void ToLower(std::string& str)
	{
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	}*/

	/*template<typename T, typename T2 = std::vector<T>>
	const bool Find(T2 haystack, T2 needle)
	{
		if (haystack.empty())
			return false;
		return (std::find(haystack.begin(), haystack.end(), needle) != haystack.end());
	}*/

}