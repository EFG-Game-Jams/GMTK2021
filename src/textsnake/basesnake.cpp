#include "basesnake.hpp"
#include <cassert>
#include "cursor.hpp"
#include "coordops.hpp"
#include "config.hpp"

void BaseSnake::Reverse()
{
	// Head becomes body part
	blocks[0].color = bodyColor;
	blocks[0].Draw();

	std::vector<SnakeBlock> reversedBlocks;
	for (long i = blocks.size() - 1; i >= 0; --i)
	{
		SnakeBlock reversedBlock = blocks[i];
		reversedBlock.color = bodyColor;
		reversedBlock.direction = GetOppositeMovingDirection(blocks[i].direction);
		reversedBlocks.push_back(reversedBlock);
	}
	
	blocks = reversedBlocks;
	blocks[0].color = headColor;
	blocks[0].Draw();

	movingDirection = blocks[0].direction;
}

void BaseSnake::Translate(COORD const offset)
{
	assert(blocks.size() > 0);
	char const clearCharacter = ' ';
	
	COORD newPos = Config::WrapToPlayArea(GetHead().position + offset);
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

	blocks[0].direction = movingDirection;
	for (std::size_t i = blocks.size() - 1; i > 0; --i)
	{
		blocks[i].direction = blocks[i - 1].direction;
	}
}

std::vector<SnakeBlock> const& BaseSnake::GetBlocks() const
{
	return blocks;
}

std::size_t const BaseSnake::GetSize() const
{
	return blocks.size();
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
	return Config::WrapToPlayArea(GetHead().position + nextMove);
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
	std::vector<SnakeBlock> const& _blocks,
	Color::Color const _headColor,
	Color::Color const _bodyColor,
	Color::Color const _clearColor)
	: blocks(_blocks),
	nextMove{ 0, 0 },
	clearColor(_clearColor),
	headColor(_headColor),
	bodyColor(_bodyColor),
	movingDirection(_blocks[0].direction)
{
	blocks[0].color = headColor;
	blocks[0].Draw();

	for (std::size_t i = 1; i < blocks.size(); ++i)
	{
		blocks[i].color = bodyColor;
		blocks[i].Draw();
	}
}

BaseSnake::~BaseSnake()
{
}

std::vector<SnakeBlock> GenerateLineOfSnakeBlocks(
	COORD const spawnPosition,
	MovingDirection const movingDirection,
	std::string const & letters,
	Color::Color const headColor,
	Color::Color const bodyColor)
{
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

	std::vector<SnakeBlock> blocks;
	for (std::size_t i = 0; i < letters.size(); ++i)
	{
		SnakeBlock block;
		block.character = letters[i];
		block.color = i == 0 ? headColor : bodyColor;
		block.position = Config::WrapToPlayArea(spawnPosition + (spawnGrowthDirection * COORD{ static_cast<short>(i), static_cast<short>(i) }));
		block.direction = movingDirection;

		blocks.push_back(block);
	}

	return blocks;
}
