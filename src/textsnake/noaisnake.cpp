#include "noaisnake.hpp"
#include "config.hpp"

void NoAiSnake::CalculateNextMove(unsigned const elapsedMs)
{
	elapsedSinceLastTick += elapsedMs;
	if (elapsedSinceLastTick >= Config::ticksPerPlayerMove)
	{
		elapsedSinceLastTick = 0;
		nextMove = GetTranslateOffsetByCurrentDirection();
	}
}

SnakeType NoAiSnake::GetType() const
{
	return SnakeType::NoAi;
}

NoAiSnake::NoAiSnake(MovingDirection const direction, COORD const spawnPosition, std::string const& letters, Color::Color const clearColor)
	: BaseSnake(direction, spawnPosition, letters, Config::dumbHeadColor, Config::dumbBodyColor, clearColor),
	elapsedSinceLastTick(0)
{
}
