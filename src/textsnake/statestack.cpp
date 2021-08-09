#include <algorithm>
#include "coordops.hpp"
#include "cursor.hpp"
#include "window.hpp"
#include "statestack.hpp"
#include "color.hpp"
#include "config.hpp"
#include <cassert>
#include "scoreoverlay.hpp"

std::size_t StateStack::GetLastIndex() const
{
	return states.size() - 1;
}

void StateStack::Clear()
{
	stackModified = true;
	for (auto iter = states.begin(); iter != states.end(); ++iter)
	{
		(*iter)->Destroy();
		toDelete.push_back(std::move(*iter));
	}
	states.clear();

	// Fix weird runtime bug outside of VS console
	std::cout << Color::Color();
	system("cls");
}

void StateStack::PushState(std::unique_ptr<State>&& state)
{
	stackModified = true;
	if (!state->IsOverlay())
	{
		Clear();
	}

	states.push_back(std::move(state));
	states[GetLastIndex()]->Focus();
}

void StateStack::PopState()
{
	assert(states.size() > 0);

	stackModified = true;
	toDelete.push_back(std::move(*states.rbegin()));
	states.resize(GetLastIndex());

	if (states.size() > 0)
	{
		states[GetLastIndex()]->Focus();
	}
}

std::size_t StateStack::StateCount() const
{
	return states.size();
}

void StateStack::Update(unsigned const elapsedMs)
{
	toDelete.clear();

	stackModified = false;
	for (auto iter = states.rbegin(); iter != states.rend(); ++iter)
	{
		(*iter)->Update(elapsedMs);
		
		if (stackModified)
		{
			// No way to properly handle this, just return
			return;
		}

		if (!(*iter)->UpdateBelow())
		{
			return;
		}
	}
}

StateStack & StateStack::GetInstance()
{
	static StateStack stateStack;

	return stateStack;
}
