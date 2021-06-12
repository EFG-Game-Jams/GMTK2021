#pragma once
#include "basesnake.hpp"

class HunterSnake : public BaseSnake
{
private:
	unsigned elapsedSinceLastDirectionChange, elapsedSinceLastMovement;

	MovingDirection CalculateDesiredMovingDirection(std::vector<std::unique_ptr<BaseSnake>> const& otherSnakes);

public:
	void CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes) override;

	SnakeType GetType() const override;

	HunterSnake(
		std::vector<SnakeBlock> const& blocks,
		Color::Color const clearColor);
};
