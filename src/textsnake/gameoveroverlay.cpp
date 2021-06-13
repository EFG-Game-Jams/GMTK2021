#include "config.hpp"
#include "userinput.hpp"
#include "statestack.hpp"
#include "gameoveroverlay.hpp"
#include "menustate.hpp"

void GameOverOverlay::Update(unsigned const elapsedMs)
{
	auto& evHandler = UserInput::GetInstance();

	if (evHandler.WasActionReleased(PlayerActions::Action))
	{
		auto& stateStack = StateStack::GetInstance();
		stateStack.PushState(std::make_unique<MenuState>());
	}
}

GameOverOverlay::GameOverOverlay()
	: MessageOverlay(
		COORD{0, Config::consoleBufferSize.Y / 2},
		Config::consoleBufferSize.X,
		"Game Over!",
		Color::Color(Color::Foreground::WHITE, Color::Background::DARKRED))
{
}
