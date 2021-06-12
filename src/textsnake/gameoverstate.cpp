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
		stateStack.PopState();
		stateStack.PushState(std::make_unique<MenuState>());
		return;
	}
	else if (evHandler.WasActionReleased(PlayerActions::Escape))
	{
		auto& stateStack = StateStack::GetInstance();
		stateStack.PopState();
		return;
	}
}

GameOverState::GameOverState()
	: MessageState(
		COORD{Config::consoleBufferSize.X, Config::consoleBufferSize.Y},
		Config::consoleBufferSize.X,
		"Game Over! Continue? Y/N",
		Color::Color(Color::Foreground::WHITE, Color::Background::DARKRED))
{
}

GameOverState::~GameOverState()
{
}
