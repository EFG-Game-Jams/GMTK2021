#include <algorithm>
#include "coordops.hpp"
#include "cursor.hpp"
#include "window.hpp"
#include "statestack.hpp"
#include "color.hpp"
#include "config.hpp"
#include <cassert>

void StateStack::Clear()
{
	states.clear();
}

void StateStack::SchedulePushState(std::unique_ptr<State>&& state)
{
	assert(pendingAction == PendingStackAction::None);
	if (state->IsOverlay())
	{
		pendingAction = PendingStackAction::Focus;
	}
	else
	{
		pendingAction = PendingStackAction::Shrink;
	}

	states.emplace_back(std::move(state));
}

void StateStack::SchedulePopState()
{
	assert(pendingAction == PendingStackAction::None);
	pendingAction = PendingStackAction::Pop;
}

std::size_t StateStack::StateCount() const
{
	return states.size();
}

State* const StateStack::GetActiveState()
{
	return activeState;
}

void StateStack::HandleScheduledAction()
{
	switch (pendingAction)
	{
	case PendingStackAction::Shrink:
		{
			for (long i = states.size() - 2; i >= 0; --i)
			{
				states[i]->Destroy();
			}

			// Clear the screen
			std::cout << Color::Color(); // Black
			std::size_t const limit = Config::consoleBufferSize.X * Config::consoleBufferSize.Y;
			for (std::size_t i = 0; i < limit; ++i)
			{
				std::cout << ' ';
			}

			if (states.size() > 1)
			{
				std::swap(states[0], states.back());
				states.resize(1);
			}
		}
		break;

	case PendingStackAction::Pop:
		assert(states.size() > 0);
		states[states.size() - 1]->Destroy();
		states.resize(states.size() - 1);
		break;

	default:
	case PendingStackAction::Focus:
	case PendingStackAction::None:
		break;
	}

	if (states.size() > 0)
	{
		activeState = states.back().get();
		activeState->Focus();
	}
	else
	{
		activeState = nullptr;
	}
	pendingAction = PendingStackAction::None;
}

StateStack & StateStack::GetInstance()
{
	static StateStack stateStack;

	return stateStack;
}

StateStack::StateStack()
	: pendingAction(PendingStackAction::None),
	activeState(nullptr)
{
}
