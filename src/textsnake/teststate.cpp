#include "teststate.hpp"
#include "config.hpp"
#include "userinput.hpp"
#include "statestack.hpp"
#include "pausestate.hpp"
#include "snakefactory.hpp"

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
	field.snakes.emplace_back(SnakeFactory::CreatePlayer(
		spawnLocation,
		MovingDirection::North,
		"PLAYER"));

	spawnLocation.X = 3;
	spawnLocation.Y = 5;
	field.snakes.emplace_back(SnakeFactory::CreateRandom(
		spawnLocation,
		MovingDirection::South,
		"RANDOM"));
	
	spawnLocation.X = 65;
	spawnLocation.Y = 15;
	field.snakes.emplace_back(SnakeFactory::CreateNoAi(
		spawnLocation,
		MovingDirection::East,
		"STATIC"));

	spawnLocation.X = 30;
	spawnLocation.Y = 15;
	field.snakes.emplace_back(SnakeFactory::CreateHunter(
		spawnLocation,
		MovingDirection::West,
		"AGGRO"));

	spawnLocation.X = 30;
	spawnLocation.Y = 15;
	field.snakes.emplace_back(SnakeFactory::CreateRandom(
		spawnLocation,
		MovingDirection::West,
		"RANDOM"));

	spawnedSnakes = true;
}

TestState::TestState()
	: spawnedSnakes(false)
{
}
