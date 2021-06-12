#pragma once
#include <windows.h>
#include <random>
#include "color.hpp"

namespace Config
{
	COORD const consoleBufferSize{ 80, 20 }; // in characters

	unsigned const ticksPerPlayerMove = 32;

	unsigned const ticksPerDumbMove = 48;
	unsigned const ticksPerDumbChangeOrientation = 800;

	Color::Color const playerHeadColor{ Color::Foreground::YELLOW, Color::Background::DARKYELLOW };
	Color::Color const playerBodyColor{ Color::Foreground::GREEN, Color::Background::DARKGREEN };

	Color::Color const dumbHeadColor{ Color::Foreground::CYAN, Color::Background::DARKCYAN };
	Color::Color const dumbBodyColor{ Color::Foreground::BLUE, Color::Background::DARKBLUE };

	// If the supplied position goes out of bounds (< 0 or > console dimension) it wraps the value
	COORD GetSafePosition(COORD position);

	// Returns a value between 0.0 and 1.0
	double GetRandomDouble();
}