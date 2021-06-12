#pragma once
#include "userinput.hpp"
#include <memory>
#include "state.hpp"
#include "pendingstackaction.h"

class StateStack
{
private:
	PendingStackAction pendingAction;
	std::vector<std::unique_ptr<State>> states;
	State* activeState;

	StateStack();
	~StateStack() = default;

public:
	void Clear();

	void SchedulePushState(std::unique_ptr<State>&& state);
	void SchedulePopState();
	std::size_t StateCount() const;
	State* const GetActiveState();

	void HandleScheduledAction();

	static StateStack & GetInstance();
};

