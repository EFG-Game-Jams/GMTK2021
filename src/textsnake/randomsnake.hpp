#pragma once
#include "basesnake.hpp"

class RandomSnake : public BaseSnake
{
private:
	unsigned elapsedSinceLastDirectionChange, elapsedSinceLastMovement;

public:
	void CalculateNextMove(unsigned const elapsedMs) override;

	SnakeType GetType() const override;

	RandomSnake(MovingDirection const initialMovingDirection,
		COORD const spawnPosition,
		std::string const& letters,
		Color::Color const clearColor);
};
