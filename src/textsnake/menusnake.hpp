#pragma once
#include "basesnake.hpp"
#include "statestack.hpp"
#include <functional>

class MenuSnake : public BaseSnake
{
private:
	SnakeType type;

public:
	virtual SnakeType GetType() const override;

	virtual void CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes) override;

	MenuSnake(
		std::vector<SnakeBlock> const& blocks,
		SnakeType const type,
		Color::Color clearColor);
};
