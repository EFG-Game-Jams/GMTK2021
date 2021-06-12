#pragma once
#include "basesnake.hpp"
#include <memory>
#include <vector>

struct PlayingField
{
	std::vector<std::unique_ptr<BaseSnake>> snakes;

	void Update(unsigned const elapsedMs);
};
