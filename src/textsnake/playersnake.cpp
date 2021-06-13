#include "playersnake.hpp"
#include "userinput.hpp"
#include "config.hpp"
#include "randomsnake.hpp"
#include <cassert>

void PlayerSnake::CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
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
	std::vector<SnakeBlock> const& blocks,
	Color::Color const clearColor)
	: BaseSnake(
		blocks,
		Config::playerHeadColor,
		Config::playerBodyColor,
		clearColor),
	elapsedSinceLastTick(0)
{
}
