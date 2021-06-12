#pragma once
#include "basesnake.hpp"
class NoAiSnake : public BaseSnake 
{
private:
	unsigned elapsedSinceLastTick;

public:
	void CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes) override;

	SnakeType GetType() const override;

	NoAiSnake(
		std::vector<SnakeBlock> const& blocks,
		Color::Color const clearColor);
};

