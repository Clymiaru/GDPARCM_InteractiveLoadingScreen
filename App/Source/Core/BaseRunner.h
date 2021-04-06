#pragma once

#include "TypeAlias.h"

#include <SFML/Graphics.hpp>

struct Resolution
{
	Uint32 Width;
	Uint32 Height;
};

class BaseRunner
{
public:
	static Resolution WindowSize;
	static Uint32 FramerateLimit;

	explicit BaseRunner(Resolution resolution,
						StringRef appName,
						Uint32 maxFramerate);

	void Run();
private:
	sf::Event m_Event;
	sf::RenderWindow m_Window;

	void ProcessEvents();
	void Update(float deltaTime);
	void Render();
};
