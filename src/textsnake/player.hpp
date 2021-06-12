#pragma once
#include "userinput.hpp"

class Player
{
private:
	int x, y;

	void DrawPlayer() const;

public:
	void HandleInput(UserInput const& input);

	Player(int const spawnX, int const spawnY);
};