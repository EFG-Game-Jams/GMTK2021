#pragma once
#include <windows.h>
#include <random>
#include "color.hpp"

namespace Config
{
	COORD const consoleBufferSize{ 80, 20 }; // in characters

	unsigned const ticksPerPlayerMove = 64;

	unsigned const ticksPerDumbMove = 64;
	unsigned const ticksPerDumbChangeOrientation = 800;

	unsigned const ticksPerHunterMove = 64;
	unsigned const ticksPerHunterChangeOrientation = 400;

	Color::Color const playerHeadColor{ Color::Foreground::YELLOW, Color::Background::DARKYELLOW };
	Color::Color const playerBodyColor{ Color::Foreground::GREEN, Color::Background::DARKGREEN };

	Color::Color const dumbHeadColor{ Color::Foreground::CYAN, Color::Background::DARKCYAN };
	Color::Color const dumbBodyColor{ Color::Foreground::BLUE, Color::Background::DARKBLUE };

	Color::Color const hunterHeadColor{ Color::Foreground::YELLOW, Color::Background::RED };
	Color::Color const hunterBodyColor{ Color::Foreground::RED, Color::Background::DARKRED };

	Color::Color const menuHeadColor{ Color::Foreground::WHITE, Color::Background::BLACK };
	Color::Color const menuBodyColor{ Color::Foreground::WHITE, Color::Background::GRAY };
	
	// If the supplied position goes out of bounds (< 0 or > console dimension) it wraps the value
	COORD GetSafePosition(COORD position);

	// Returns a value between 0.0 and 1.0
	double GetRandomDouble();
}