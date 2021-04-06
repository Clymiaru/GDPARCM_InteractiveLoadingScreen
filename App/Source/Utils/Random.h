#pragma once
#include <random>

class Random
{
public:
	static int GetInt(int min,
                      int max);

	static float GetFloat(float min,
                          float max);

	static bool GetBool();

private:
	static std::random_device m_Generator;
};
