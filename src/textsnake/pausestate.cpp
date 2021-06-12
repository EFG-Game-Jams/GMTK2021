#include "config.hpp"
#include "userinput.hpp"
#include "statestack.hpp"
#include "pausestate.hpp"

void PauseState::Update(unsigned const elapsedMs)
{
	UserInput& evHandler = UserInput::GetInstance();
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		StateStack::GetInstance().SchedulePopState();
	}
}

PauseState::PauseState()
	: MessageState(
		COORD{ 0, Config::consoleBufferSize.Y / 2 },
		Config::consoleBufferSize.X,
		"Game is paused",
		Color::Color(Color::Foreground::WHITE, Color::Background::BLUE))
{
}
