#include "playersnake.hpp"
#include "userinput.hpp"
#include "config.hpp"
#include "randomsnake.hpp"
#include <cassert>

void PlayerSnake::CalculateNextMove(unsigned const elapsedMs)
{
	auto const& input = UserInput::GetInstance();
	if (input.WasActionPressed(PlayerActions::MoveUp))
	{
		ChangeDirection(MovingDirection::North);
	}
	else if (input.WasActionPressed(PlayerActions::MoveDown))
	{
		ChangeDirection(MovingDirection::South);
	}

	if (input.WasActionPressed(PlayerActions::MoveRight))
	{
		ChangeDirection(MovingDirection::East);
	}
	else if (input.WasActionPressed(PlayerActions::MoveLeft))
	{
		ChangeDirection(MovingDirection::West);
	}

	elapsedSinceLastTick += elapsedMs;
	if (elapsedSinceLastTick >= Config::ticksPerPlayerMove)
	{
		elapsedSinceLastTick = 0;
		nextMove = GetTranslateOffsetByCurrentDirection();
	}
}

SnakeType PlayerSnake::GetType() const
{
	return SnakeType::Player;
}

PlayerSnake::PlayerSnake(
	COORD const spawnPosition,
	std::string const & letters,
	Color::Color const clearColor)
	: BaseSnake(
		GenerateLineOfSnakeBlocks(
			spawnPosition,
			MovingDirection::North,
			letters,
			Config::playerHeadColor,
			Config::playerBodyColor),
		Config::playerHeadColor,
		Config::playerBodyColor,
		clearColor),
	elapsedSinceLastTick(0)
{
}
