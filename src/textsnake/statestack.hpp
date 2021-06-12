#pragma once
#include "userinput.hpp"
#include <memory>
#include "gamestate.hpp"

class StateStack
{
private:
	std::vector<std::unique_ptr<GameState>> states;

	StateStack() = default;
	~StateStack() = default;

public:
	void Clear();

	void PushState(std::unique_ptr<GameState>&& state, bool clearScreen = false);
	void PopState();
	std::size_t StateCount() const;
	GameState* const GetTopState();

	static StateStack & GetInstance();
};

