#include "teststate.hpp"
#include "config.hpp"
#include "userinput.hpp"
#include "statestack.hpp"
#include "snakefactory.hpp"
#include "scoreoverlay.hpp"

void TestState::Update(unsigned const elapsedMs)
{
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

	// Clear the screen
	State::Focus();

	COORD spawnLocation;
	Color::Color clearColor;

	spawnLocation.X = Config::playAreaSize.X / 2;
	spawnLocation.Y = Config::playAreaSize.Y / 2;
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

	spawnLocation.X = 40;
	spawnLocation.Y = 1;
	field.snakes.emplace_back(SnakeFactory::CreateRandom(
		spawnLocation,
		MovingDirection::West,
		"RANDOM"));

	spawnedSnakes = true;

	StateStack::GetInstance().PushState(std::make_unique<ScoreOverlay>());
}

TestState::TestState()
	: spawnedSnakes(false)
{
}
