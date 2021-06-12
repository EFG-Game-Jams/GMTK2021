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
	blocks[blocks.size() - 1].Draw();

	blocks[0].color = headColor;
	blocks[0].Draw();

	movingDirection = GetOppositeMovingDirection(movingDirection);
}

void BaseSnake::Translate(COORD const offset)
{
	assert(blocks.size() > 0);
	char const clearCharacter = ' ';
	
	COORD newPos = Config::GetSafePosition(GetHead().position + offset);
	MovingDirection newMovingDirection = movingDirection;
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
		std::swap(blocks[i].direction, newMovingDirection);
		blocks[i].Draw();
	}
}

std::vector<SnakeBlock> const& BaseSnake::GetBlocks() const
{
	return blocks;
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
	else
	{
		movingDirection = newDirection;
	}
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

MovingDirection BaseSnake::GetMovingDirection() const
{
	return movingDirection;
}

Color::Color BaseSnake::GetClearColor() const
{
	return clearColor;
}

void BaseSnake::ForceMove()
{
	nextMove = GetTranslateOffsetByCurrentDirection();
	ApplyNextMove();
}

void BaseSnake::ForceFreeze()
{
	nextMove.X = 0;
	nextMove.Y = 0;
}

void BaseSnake::Update()
{
	ApplyNextMove();
}

void BaseSnake::Prepend(BaseSnake const& other)
{
	movingDirection = other.movingDirection;

	blocks[0].color = bodyColor;

	for (long i = other.blocks.size() - 1; i >= 0; --i)
	{
		auto newBlock = other.blocks[i];
		newBlock.color = bodyColor;

		blocks.insert(blocks.begin(), newBlock);
	}

	blocks[0].color = headColor;
}

void BaseSnake::Trim(std::size_t newSize)
{
	blocks.resize(newSize);
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
		block.direction = initialMovingDirection;

		block.Draw();
		blocks.push_back(block);
	}
}

BaseSnake::~BaseSnake()
{
}
