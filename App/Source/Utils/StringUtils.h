#pragma once
#include <string>
#include <vector>
#include "TypeAlias.h"

namespace Utils::String
{
	auto split(StringRef s,
	           char delimiter) -> std::vector<std::string>;
};
