#include "config.hpp"
#include "userinput.hpp"
#include "statestack.hpp"
#include "gameoverstate.hpp"
#include "menustate.hpp"

void GameOverState::Update(unsigned const elapsedMs)
{
	auto& evHandler = UserInput::GetInstance();

	if (evHandler.WasActionReleased(PlayerActions::Action))
	{
		auto& stateStack = StateStack::GetInstance();
		stateStack.SchedulePushState(std::make_unique<MenuState>());
	}
}

GameOverState::GameOverState()
	: MessageState(
		COORD{0, Config::consoleBufferSize.Y / 2},
		Config::consoleBufferSize.X,
		"Game Over!",
		Color::Color(Color::Foreground::WHITE, Color::Background::DARKRED))
{
}
