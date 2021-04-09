#include "pch.h"
#include "Core/BaseRunner.h"

auto main(const int argc, const char** argv) -> int
{
	auto app = BaseRunner({1280, 720}, "Interactive Loading Screen");
	app.Run();
}
