#include "config.hpp"
#include "color.hpp"
#include "coordops.hpp"
#include "cursor.hpp"
#include "window.hpp"
#include "statestack.hpp"
#include "playingstate.hpp"
#include "pausestate.hpp"

void PlayingState::Pause()
{
	StateStack& stateStack = StateStack::GetInstance();
	stateStack.PushState(std::make_unique<PauseState>());
}

void PlayingState::HandleInput(UserInput const& evHandler)
{
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		Pause();
		return;
	}

	player.HandleInput(evHandler);
}

void PlayingState::Update(unsigned const elapsedMs)
{
	UserInput& evHandler = UserInput::GetInstance();
	if (evHandler.WasThereAnyAction())
	{
		HandleInput(evHandler);
	}

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(stdoutHandle, &csbi);
}

void PlayingState::Awake()
{
	
}

PlayingState::PlayingState()
	: player(Config::consoleBufferSize.X / 2, Config::consoleBufferSize.Y / 2)
{
}

PlayingState::~PlayingState()
{
}
