#pragma once
#include "userinput.hpp"
#include "statestack.hpp"
#include "level.hpp"

class Game
{
private:
	UserInput& userInput;
	StateStack& stateStack;

	void Reset(Level startupLevel = Level::Unknown);

	void HandleInput();

public:
	void Run(long long const targetFrameTime, Level startupLevel);

	Game();
	~Game();
};

