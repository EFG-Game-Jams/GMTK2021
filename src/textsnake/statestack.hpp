#pragma once
#include "userinput.hpp"
#include <memory>
#include "basestate.hpp"

class StateStack
{
private:
	std::vector<std::unique_ptr<State>> states;

	StateStack() = default;
	~StateStack() = default;

public:
	void Clear();

	void PushState(std::unique_ptr<State>&& state);
	void PopState();
	std::size_t StateCount() const;
	State* const GetTopState();

	static StateStack & GetInstance();
};

