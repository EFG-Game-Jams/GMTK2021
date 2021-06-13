#include "state.hpp"
#include "color.hpp"
#include "config.hpp"

bool State::IsOverlay() const
{
	return false;
}

bool State::UpdateBelow() const
{
	return false;
}

void State::Focus()
{
	// Clear the screen
	std::cout << Color::Color(); // Black
	std::size_t const limit = Config::consoleBufferSize.X * Config::consoleBufferSize.Y;
	for (std::size_t i = 0; i < limit; ++i)
	{
		std::cout << ' ';
	}
}
