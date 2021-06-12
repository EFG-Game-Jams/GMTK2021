#include "config.hpp"
#include "color.hpp"
#include "coordops.hpp"
#include "cursor.hpp"
#include "window.hpp"
#include "statestack.hpp"
#include "menustate.hpp"
#include "pausestate.hpp"
#include "playersnake.hpp"
#include "dumbsnake.hpp"

void MenuState::Pause()
{
	StateStack& stateStack = StateStack::GetInstance();
	stateStack.PushState(std::make_unique<PauseState>());
}

void MenuState::HandleInput(UserInput const& evHandler)
{
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		Pause();
		return;
	}
}

void MenuState::Update(unsigned const elapsedMs)
{
	UserInput& evHandler = UserInput::GetInstance();
	if (evHandler.WasThereAnyAction())
	{
		HandleInput(evHandler);
	}

	field.Update(elapsedMs);
}

void MenuState::Awake()
{
	
}

MenuState::MenuState()
{
	COORD spawnLocation;
	Color::Color clearColor;

	spawnLocation.X = Config::consoleBufferSize.X / 2;
	spawnLocation.Y = Config::consoleBufferSize.Y / 2;
	field.snakes.emplace_back(std::make_unique<PlayerSnake>(spawnLocation, std::string("PLAY"), clearColor));

	spawnLocation.X = static_cast<short>(Config::consoleBufferSize.X * 0.25);
	spawnLocation.Y = static_cast<short>(Config::consoleBufferSize.Y * 0.25);
	field.snakes.emplace_back(std::make_unique<DumbSnake>(MovingDirection::East, spawnLocation, std::string("LA"), clearColor));

	spawnLocation.X = static_cast<short>(Config::consoleBufferSize.X * 0.75);
	spawnLocation.Y = static_cast<short>(Config::consoleBufferSize.Y * 0.33);
	field.snakes.emplace_back(std::make_unique<DumbSnake>(MovingDirection::South, spawnLocation, std::string("Y"), clearColor));
}

MenuState::~MenuState()
{
}
