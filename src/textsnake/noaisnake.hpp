#pragma once
#include "basesnake.hpp"
class NoAiSnake : public BaseSnake 
{
private:
	unsigned elapsedSinceLastTick;

public:
	void CalculateNextMove(unsigned const elapsedMs) override;

	SnakeType GetType() const override;

	NoAiSnake(MovingDirection const direction, COORD const spawnPosition, std::string const& letters, Color::Color const clearColor);
};

