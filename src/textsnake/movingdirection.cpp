#include "movingdirection.hpp"
#include <cassert>

MovingDirection GetOppositeMovingDirection(MovingDirection d)
{
	switch (d)
	{
	case MovingDirection::North:
		return MovingDirection::South;

	case MovingDirection::South:
		return MovingDirection::North;

	case MovingDirection::East:
		return MovingDirection::West;

	case MovingDirection::West:
		return MovingDirection::East;
	}

	assert(false);
}

bool IsOppositeMovingDirection(MovingDirection a, MovingDirection b)
{
	return GetOppositeMovingDirection(a) == b;
}