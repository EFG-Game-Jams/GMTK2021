#pragma once
#include <vector>
#include <memory>
#include "movingdirection.hpp"
#include "snakeblock.hpp"
#include "snaketype.hpp"

std::vector<SnakeBlock> GenerateLineOfSnakeBlocks(
	COORD const spawnPosition,
	MovingDirection const movingDirection,
	std::string const& letters,
	Color::Color const headColor,
	Color::Color const bodyColor);

class BaseSnake
{
protected:
	std::vector<SnakeBlock> blocks;
	MovingDirection movingDirection;
	Color::Color clearColor, headColor, bodyColor;
	COORD nextMove;

	// Moves all the blocks by the offset
	// Redraws the snake
	void Translate(COORD const offset);

	void ChangeDirection(MovingDirection const newDirection);

	COORD GetTranslateOffsetByCurrentDirection() const;
	void ApplyNextMove();

public:
	// Reverse the snake => make the tail the head
	void Reverse();

	virtual SnakeType GetType() const = 0;
	std::vector<SnakeBlock> const& GetBlocks() const;
	std::size_t const& GetSize() const;
	SnakeBlock const& GetHead() const;
	COORD GetNextHeadPosition() const;
	MovingDirection GetMovingDirection() const;
	Color::Color GetClearColor() const;

	// Forces the snake to move 1 unit in the direction it currently faces
	void ForceMove();
	// Forces the snake to abort its next move
	void ForceFreeze();

	virtual void CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes) = 0;
	virtual void Update();

	// Other becomes new head of this, this becomes the tail
	virtual void Prepend(BaseSnake const& other);
	virtual void Trim(std::size_t newSize);

	BaseSnake(
		std::vector<SnakeBlock> const & blocks,
		Color::Color const headColor,
		Color::Color const bodyColor,
		Color::Color const clearColor);

	virtual ~BaseSnake();
};

