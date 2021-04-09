#pragma once
#include <SFML/Graphics.hpp>

#include "Utils/TypeAlias.h"

struct Resolution
{
	Uint Width;
	Uint Height;
};

class BaseRunner
{
public:
	static Resolution WindowSize;

	BaseRunner(Resolution windowSize,
			   StringRef title);
	void Run();

private:
	sf::Event m_Event;
	sf::RenderWindow m_Window;
	
	void Render();
	void ProcessEvents();
	void Update(float deltaTime);
};
