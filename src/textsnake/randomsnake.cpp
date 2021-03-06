#include "randomsnake.hpp"
#include "config.hpp"
#include <cassert>

void RandomSnake::CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
{
	elapsedSinceLastDirectionChange += elapsedMs;
	elapsedSinceLastMovement += elapsedMs;

	if (elapsedSinceLastDirectionChange >= Config::ticksPerDumbChangeOrientation)
	{
		elapsedSinceLastDirectionChange = 0;

		switch (movingDirection)
		{
		case MovingDirection::North:
		case MovingDirection::South:
			if (Config::GetRandomDouble() < 0.5)
			{
				ChangeDirection(MovingDirection::East);
			}
			else
			{
				ChangeDirection(MovingDirection::West);
			}
			break;

		case MovingDirection::East:
		case MovingDirection::West:
			if (Config::GetRandomDouble() < 0.5)
			{
				ChangeDirection(MovingDirection::North);
			}
			else
			{
				ChangeDirection(MovingDirection::South);
			}
			break;

			if (Config::GetRandomDouble() < 0.5)
			{
				ChangeDirection(MovingDirection::East);
			}
			else
			{
				ChangeDirection(MovingDirection::West);
			}
			break;
		}
	}

	if (elapsedSinceLastMovement >= Config::ticksPerDumbMove)
	{
		elapsedSinceLastMovement = 0;
		nextMove = GetTranslateOffsetByCurrentDirection();
	}
}

SnakeType RandomSnake::GetType() const
{
	return SnakeType::Random;
}

RandomSnake::RandomSnake(
	std::vector<SnakeBlock> const& blocks,
	Color::Color const clearColor)
	: BaseSnake(blocks, Config::dumbHeadColor, Config::dumbBodyColor, clearColor),
	elapsedSinceLastDirectionChange(0),
	elapsedSinceLastMovement(0)
{
}
