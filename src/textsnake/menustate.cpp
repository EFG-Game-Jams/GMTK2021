#include "config.hpp"
#include "color.hpp"
#include "coordops.hpp"
#include "cursor.hpp"
#include "window.hpp"
#include "statestack.hpp"
#include "menustate.hpp"
#include "pausestate.hpp"
#include "playersnake.hpp"
#include "randomsnake.hpp"
#include "noaisnake.hpp"

void MenuState::Update(unsigned const elapsedMs)
{
	UserInput& evHandler = UserInput::GetInstance();
	if (evHandler.WasActionReleased(PlayerActions::Pause))
	{
		StateStack& stateStack = StateStack::GetInstance();
		stateStack.PushState(std::make_unique<PauseState>());
		return;
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
	field.snakes.emplace_back(std::make_unique<PlayerSnake>(spawnLocation, std::string("ABCDEFGHIJKLM"), clearColor));

	//spawnLocation.X = static_cast<short>(Config::consoleBufferSize.X * 0.25);
	//spawnLocation.Y = static_cast<short>(Config::consoleBufferSize.Y * 0.25);
	//field.snakes.emplace_back(std::make_unique<NoAiSnake>(MovingDirection::East, spawnLocation, std::string("123456"), clearColor));

	//spawnLocation.X = static_cast<short>(Config::consoleBufferSize.X * 0.75);
	//spawnLocation.Y = static_cast<short>(Config::consoleBufferSize.Y * 0.33);
	//field.snakes.emplace_back(std::make_unique<RandomSnake>(MovingDirection::South, spawnLocation, std::string("AAAAAAAA"), clearColor));
}

MenuState::~MenuState()
{
}
