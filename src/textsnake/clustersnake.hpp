#pragma once
#include "basesnake.hpp"

class ClusterSnake : public BaseSnake
{
private:
	unsigned elapsedSinceLastDirectionChange, elapsedSinceLastMovement;

	typedef bool (*SnakeFilter)(BaseSnake const*);

	MovingDirection CalculateDesiredMovingDirection(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes);
	BaseSnake const* FindNearestSnake(std::vector<std::unique_ptr<BaseSnake>> const& snakes, int x, int y, SnakeFilter filter, int &outDistance, COORD &outBlock) const;

public:
	void CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes) override;

	SnakeType GetType() const override;

	ClusterSnake(
		std::vector<SnakeBlock> const& blocks,
		Color::Color const clearColor);
};
