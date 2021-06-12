#include "coordops.hpp"

COORD operator -(const COORD a, const COORD b)
{
	COORD result;
	result.X = a.X - b.X;
	result.Y = a.Y - b.Y;

	return result;
}

COORD operator +(const COORD a, const COORD b)
{
	COORD result;
	result.X = a.X + b.X;
	result.Y = a.Y + b.Y;

	return result;
}

COORD operator *(const COORD a, const COORD b)
{
	COORD result;
	result.X = a.X * b.X;
	result.Y = a.Y * b.Y;

	return result;
}

COORD operator /(const COORD a, const COORD b)
{
	COORD result;
	result.X = a.X / b.X;
	result.Y = a.Y / b.Y;

	return result;
}

bool operator==(const COORD a, const COORD b)
{
	return a.X == b.X && a.Y == b.Y;
}

bool operator!=(const COORD a, const COORD b)
{
	return !(a == b);
}
