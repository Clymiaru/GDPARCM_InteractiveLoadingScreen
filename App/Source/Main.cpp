#include <pch.h>
#include "Core/BaseRunner.h"

auto main (const int argc, const char** argv) -> int
{
	auto app = BaseRunner({1280U, 720U},
						  "App",
						  60);
	app.Run();
}