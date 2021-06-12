#include "noaisnake.hpp"
#include "config.hpp"

void NoAiSnake::CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
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

NoAiSnake::NoAiSnake(
	std::vector<SnakeBlock> const& blocks,
	Color::Color const clearColor)
	: BaseSnake(blocks, Config::dumbHeadColor, Config::dumbBodyColor, clearColor),
	elapsedSinceLastTick(0)
{
}
