#include "config.hpp"

COORD Config::GetSafePosition(COORD position)
{
	if (position.X < 0)
	{
		position.X = Config::consoleBufferSize.X - 1;
	}
	else if (position.X >= Config::consoleBufferSize.X)
	{
		position.X = 0;
	}

	if (position.Y < 0)
	{
		position.Y = Config::consoleBufferSize.Y - 1;
	}
	else if (position.Y >= Config::consoleBufferSize.Y)
	{
		position.Y = 0;
	}

	return position;
}

double Config::GetRandomDouble()
{
	static std::default_random_engine dre;
	static std::uniform_real_distribution<double> dist(0.0, 1.0);

	return dist(dre);
}
