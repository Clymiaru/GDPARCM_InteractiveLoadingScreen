#include "pch.h"
#include "StringUtils.h"
#include <sstream>

namespace Utils::String
{
	auto split(StringRef s,
	           const char delimiter) -> std::vector<std::string>
	{
		std::vector<std::string> tokens;
		std::string token;
		std::istringstream tokenStream(s);
		while (std::getline(tokenStream, token, delimiter))
			tokens.push_back(token);
		return tokens;
	}
}
