#pragma once

enum class MovingDirection
{
	North,
	South,
	East,
	West
};

MovingDirection GetOppositeMovingDirection(MovingDirection d);
bool IsOppositeMovingDirection(MovingDirection a, MovingDirection b);

MovingDirection GetOrthogonalMovingDirection(MovingDirection d);
