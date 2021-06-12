#pragma once
#include "basesnake.hpp"

class DumbSnake : public BaseSnake
{
private:
	unsigned elapsedSinceLastDirectionChange, elapsedSinceLastMovement;

public:
	void CalculateNextMove(unsigned const elapsedMs) override;

	DumbSnake(MovingDirection const initialMovingDirection,
		COORD const spawnPosition,
		std::string const& letters,
		Color::Color const clearColor);
};
