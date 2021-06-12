#pragma once
#include "coordops.hpp"
#include "color.hpp"
#include "movingdirection.hpp"

struct SnakeBlock
{
	char character;
	COORD position;
	Color::Color color;
	MovingDirection direction;

	// Does not clear its previous position!
	void Draw() const;
};

