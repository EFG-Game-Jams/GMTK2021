#pragma once
#include "basesnake.hpp"
class NoAiSnake : public BaseSnake 
{
private:
	unsigned elapsedSinceLastTick;

public:
	void CalculateNextMove(unsigned const elapsedMs) override;

	SnakeType GetType() const override;

	NoAiSnake(
		std::vector<SnakeBlock> const& blocks,
		Color::Color const clearColor);
};

