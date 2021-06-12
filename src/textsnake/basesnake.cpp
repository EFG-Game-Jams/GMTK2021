#include "basesnake.hpp"
#include <cassert>
#include "cursor.hpp"
#include "coordops.hpp"
#include "config.hpp"

void BaseSnake::Reverse()
{
	for (std::size_t i = 0; i < blocks.size() / 2; ++i)
	{
		std::swap(blocks[i], blocks[blocks.size() - (i + 1)]);
	}

	blocks[blocks.size() - 1].color = bodyColor;
	blocks[0].color = headColor;
	blocks[0].Draw();
}

void BaseSnake::Translate(COORD const offset)
{
	assert(blocks.size() > 0);
	char const clearCharacter = ' ';
	
	COORD newPos = Config::GetSafePosition(GetHead().position + offset);
	for (std::size_t i = 0; i < blocks.size(); ++i)
	{
		if (i == blocks.size() - 1)
		{
			std::cout
				<< clearColor
				<< blocks[i].position
				<< clearCharacter;
		}

		std::swap(blocks[i].position, newPos);
		blocks[i].Draw();
	}
}

SnakeBlock const& BaseSnake::GetHead() const
{
	assert(blocks.size() > 0);

	return blocks[0];
}

void BaseSnake::ChangeDirection(MovingDirection const newDirection)
{
	if (IsOppositeMovingDirection(newDirection, movingDirection))
	{
		Reverse();
	}
	movingDirection = newDirection;
}

COORD BaseSnake::GetTranslateOffsetByCurrentDirection() const
{
	COORD offset{ 0, 0 };
	switch (movingDirection)
	{
	case MovingDirection::North:
		offset.Y = -1;
		break;

	case MovingDirection::South:
		offset.Y = 1;
		break;

	case MovingDirection::West:
		offset.X = -1;
		break;

	case MovingDirection::East:
		offset.X = 1;
		break;
	}

	return offset;
}

void BaseSnake::ApplyNextMove()
{
	if (nextMove.X == 0 && nextMove.Y == 0)
	{
		return;
	}

	Translate(nextMove);

	nextMove.X = 0;
	nextMove.Y = 0;
}

COORD BaseSnake::GetNextHeadPosition() const
{
	return Config::GetSafePosition(GetHead().position + nextMove);
}

void BaseSnake::Update()
{
	ApplyNextMove();
}

BaseSnake::BaseSnake(
	MovingDirection const initialMovingDirection,
	COORD const spawnPosition,
	std::string const& letters,
	Color::Color const _headColor,
	Color::Color const _bodyColor,
	Color::Color const _clearColor)
	: nextMove{0, 0},
	clearColor(_clearColor),
	headColor(_headColor),
	bodyColor(_bodyColor)
{
	movingDirection = initialMovingDirection;
	
	COORD spawnGrowthDirection{ 0, 0 };
	switch (movingDirection)
	{
	case MovingDirection::North:
		spawnGrowthDirection.Y = 1;
		break;

	case MovingDirection::South:
		spawnGrowthDirection.Y = -1;
		break;

	case MovingDirection::West:
		spawnGrowthDirection.X = 1;
		break;

	case MovingDirection::East:
		spawnGrowthDirection.X = -1;
		break;
	}

	for (std::size_t i = 0; i < letters.size(); ++i)
	{
		SnakeBlock block;
		block.character = letters[i];
		block.color = i == 0 ? headColor : bodyColor;
		block.position = Config::GetSafePosition(spawnPosition + (spawnGrowthDirection * COORD{ static_cast<short>(i), static_cast<short>(i) }));

		block.Draw();
		blocks.push_back(block);
	}
}

BaseSnake::~BaseSnake()
{
	for (std::size_t i = 0; i < blocks.size(); ++i)
	{
		blocks[i].color = clearColor;
		blocks[i].Draw();
	}
}

MovingDirection GetOppositeMovingDirection(MovingDirection d)
{
	switch (d)
	{
	case MovingDirection::North:
		return MovingDirection::South;

	case MovingDirection::South:
		return MovingDirection::North;

	case MovingDirection::East:
		return MovingDirection::West;

	case MovingDirection::West:
		return MovingDirection::East;
	}

	assert(false);
}

bool IsOppositeMovingDirection(MovingDirection a, MovingDirection b)
{
	return GetOppositeMovingDirection(a) == b;
}
