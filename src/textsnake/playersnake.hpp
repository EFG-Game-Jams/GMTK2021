#pragma once
#include "basesnake.hpp"

class PlayerSnake : public BaseSnake
{
private:
	unsigned elapsedSinceLastTick;

public:
	void CalculateNextMove(unsigned const elapsedMs) override;

	SnakeType GetType() const override;

	PlayerSnake(COORD const spawnPosition, std::string const & letters, Color::Color const clearColor);
};

