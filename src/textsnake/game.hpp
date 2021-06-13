#pragma once
#include "userinput.hpp"
#include "statestack.hpp"

class Game
{
private:
	UserInput& userInput;
	StateStack& stateStack;

	void Reset(int level = -2);

	void HandleInput();

public:
	void Run(long long const targetFrameTime, int level = -2);

	Game();
	~Game();
};

