#include "snakeblock.hpp"
#include "cursor.hpp"

void SnakeBlock::Draw() const
{
	std::cout << position << color << character;
}
