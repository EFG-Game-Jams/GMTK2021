#pragma once
#include "snakeblock.hpp"
#include <vector>

enum class MovingDirection
{
	North,
	South,
	East,
	West
};

MovingDirection GetOppositeMovingDirection(MovingDirection d);
bool IsOppositeMovingDirection(MovingDirection a, MovingDirection b);

class BaseSnake
{
protected:
	std::vector<SnakeBlock> blocks;
	MovingDirection movingDirection;
	Color::Color clearColor, headColor, bodyColor;
	COORD nextMove;

	// Reverse the snake => make the tail the head
	void Reverse();

	// Moves all the blocks by the offset
	// Redraws the snake
	void Translate(COORD const offset);

	SnakeBlock const & GetHead() const;

	void ChangeDirection(MovingDirection const newDirection);

	COORD GetTranslateOffsetByCurrentDirection() const;
	void ApplyNextMove();

public:
	COORD GetNextHeadPosition() const;

	virtual void CalculateNextMove(unsigned const elapsedMs) = 0;
	virtual void Update();

	BaseSnake(
		MovingDirection const initialMovingDirection,
		COORD const spawnPosition,
		std::string const& letters,
		Color::Color const headColor,
		Color::Color const bodyColor,
		Color::Color const clearColor);

	virtual ~BaseSnake();
};

