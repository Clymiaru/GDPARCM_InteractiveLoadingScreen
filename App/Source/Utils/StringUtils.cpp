#include "pch.h"
#include "StringUtils.h"
#include <sstream>

namespace StringUtils
{
	std::vector<std::string> split(const std::string& s,
	                               const char delimiter)
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
		{
			tokens.push_back(token);
		}
		return tokens;
	}
}
