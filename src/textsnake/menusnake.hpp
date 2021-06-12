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
		COORD const position,
		std::string const & label,
		SnakeType const type,
		Color::Color clearColor);
};
