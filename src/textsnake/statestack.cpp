#include <algorithm>
#include "coordops.hpp"
#include "cursor.hpp"
#include "window.hpp"
#include "statestack.hpp"
#include "color.hpp"
#include "config.hpp"

void StateStack::Clear()
{
	states.clear();
}

void StateStack::PushState(std::unique_ptr<GameState>&& state, bool clearScreen)
{
	if (clearScreen)
	{
		std::cout << Color::Color(); // Black
		std::size_t const limit = Config::consoleBufferSize.X * Config::consoleBufferSize.Y;
		for (std::size_t i = 0; i < limit; ++i)
		{
			std::cout << ' ';
		}
	}

	states.emplace_back(std::move(state));
	states.back()->Awake();
}

void StateStack::PopState()
{
	states.pop_back();
	if (!states.empty())
	{
		states.back()->Awake();
	}
}

std::size_t StateStack::StateCount() const
{
	return states.size();
}

GameState* const StateStack::GetTopState()
{
	if (!states.empty())
	{
		return states.back().get();
	}

	return nullptr;
}

StateStack & StateStack::GetInstance()
{
	static StateStack stateStack;

	return stateStack;
}
