#pragma once
#include <windows.h>
#include <random>
#include "color.hpp"

namespace Config
{
	COORD const consoleBufferSize{ 80, 20 }; // in characters
	COORD const playAreaSize{ consoleBufferSize.X, consoleBufferSize.Y - 1 }; // in characters, origin at {0, 0}

	unsigned const ticksPerPlayerMove = 64;

	unsigned const ticksPerDumbMove = 64;
	unsigned const ticksPerDumbChangeOrientation = 800;

	unsigned const ticksPerHunterMove = 64;
	unsigned const ticksPerHunterChangeOrientation = 400;

	unsigned const ticksPerMenuMove = 64;
	unsigned const menuMaxDriftDistance = 6;
	double const menuMoveProbability = .2;

	unsigned const scoreSplit = 5;
	unsigned const scoreConsumeHeadBase = 10;
	unsigned const scoreConsumeHeadBlock = 1;
	unsigned const scoreConsumeTailBase = 100;
	unsigned const scoreConsumeTailBlock = 10;

	Color::Color const scoreBoardColor{ Color::Foreground::WHITE, Color::Background::BLUE };

	Color::Color const playerHeadColor{ Color::Foreground::YELLOW, Color::Background::DARKYELLOW };
	Color::Color const playerBodyColor{ Color::Foreground::GREEN, Color::Background::DARKGREEN };

	Color::Color const dumbHeadColor{ Color::Foreground::CYAN, Color::Background::DARKCYAN };
	Color::Color const dumbBodyColor{ Color::Foreground::BLUE, Color::Background::DARKBLUE };

	Color::Color const hunterHeadColor{ Color::Foreground::YELLOW, Color::Background::RED };
	Color::Color const hunterBodyColor{ Color::Foreground::RED, Color::Background::DARKRED };

	Color::Color const menuHeadColor{ Color::Foreground::BLACK, Color::Background::WHITE };
	Color::Color const menuBodyColor{ Color::Foreground::BLACK, Color::Background::GRAY };
	
	// If the supplied position goes out of bounds (< 0 or > console dimension) it wraps the value
	COORD WrapToPlayArea(COORD position);

	// Returns a value between 0.0 and 1.0
	double GetRandomDouble();
}