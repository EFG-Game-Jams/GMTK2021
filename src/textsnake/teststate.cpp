
#include "teststate.hpp"
#include "config.hpp"
#include "playersnake.hpp"
#include "huntersnake.hpp"
#include "userinput.hpp"
#include "statestack.hpp"
#include "pausestate.hpp"

void TestState::Update(unsigned const elapsedMs)
{
	auto& userInput = UserInput::GetInstance();
	if (userInput.WasActionPressed(PlayerActions::Pause))
	{
		auto & stack = StateStack::GetInstance();
		stack.SchedulePushState(std::make_unique<PauseState>());

		// Avoid the upcoming update
		return;
	}

	// 
	// StateStack::GetInstance() can be used to manipulate the game state stack,
	// e.g. Clear() it and SchedulePushState(...) the MenuState to return to the main menu
	// or to push a MessageState (e.g. PauseState or GameOverState)
	field.Update(elapsedMs);
}

void TestState::Destroy()
{
	// Called when the state is about to be thrown off the stack
}

void TestState::Focus()
{
	// Called when the state is put on the stack or after gains back focus (i.e. due
	// to another state being popped off)

	if (spawnedSnakes)
	{
		return;
	}

	COORD spawnLocation;
	Color::Color clearColor;

	spawnLocation.X = Config::consoleBufferSize.X / 2;
	spawnLocation.Y = Config::consoleBufferSize.Y / 2;
	field.snakes.emplace_back(std::make_unique<PlayerSnake>(spawnLocation, std::string("ABCDEFGHIJKLM"), clearColor));

	spawnLocation.X = static_cast<short>(Config::consoleBufferSize.X * 0.25);
	spawnLocation.Y = static_cast<short>(Config::consoleBufferSize.Y * 0.75);
	field.snakes.emplace_back(std::make_unique<HunterSnake>(GenerateLineOfSnakeBlocks(spawnLocation, MovingDirection::North, "A1B2C3", Config::hunterHeadColor, Config::hunterBodyColor), clearColor));

	spawnedSnakes = true;
}

TestState::TestState()
	: spawnedSnakes(false)
{
}
