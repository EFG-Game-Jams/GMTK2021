#pragma once
#include "basesnake.hpp"

class RandomSnake : public BaseSnake
{
private:
	unsigned elapsedSinceLastDirectionChange, elapsedSinceLastMovement;

public:
	void CalculateNextMove(unsigned const elapsedMs) override;

	SnakeType GetType() const override;

	RandomSnake(
		std::vector<SnakeBlock> const& blocks,
		Color::Color const clearColor);
};
