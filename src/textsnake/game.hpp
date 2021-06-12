#pragma once
#include "userinput.hpp"
#include "statestack.hpp"

class Game
{
private:
	UserInput& userInput;
	StateStack& stateStack;

	void Reset();

	void HandleInput();

public:
	void Run(long long const targetFrameTime);

	Game();
	~Game();
};

