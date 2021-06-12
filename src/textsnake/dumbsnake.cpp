#include "dumbsnake.hpp"
#include "config.hpp"

void DumbSnake::CalculateNextMove(unsigned const elapsedMs)
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

DumbSnake::DumbSnake(MovingDirection const initialMovingDirection, COORD const spawnPosition, std::string const& letters, Color::Color const clearColor)
	: BaseSnake(initialMovingDirection,
		spawnPosition,
		letters,
		Config::dumbHeadColor,
		Config::dumbBodyColor,
		clearColor),
	elapsedSinceLastDirectionChange(0),
	elapsedSinceLastMovement(0)
{
}
