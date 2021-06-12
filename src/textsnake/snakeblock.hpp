#pragma once
#include "coordops.hpp"
#include "color.hpp"

struct SnakeBlock
{
	char character;
	COORD position;
	Color::Color color;

	// Does not clear its previous position!
	void Draw() const;
};

