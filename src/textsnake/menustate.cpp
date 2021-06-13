#include "config.hpp"
#include "menustate.hpp"
#include "snakefactory.hpp"

void MenuState::Update(unsigned const elapsedMs)
{
	field.Update(elapsedMs);
}

void MenuState::Focus()
{
	if (spawnedSnakes)
	{
		return;
	}

	// Clear the screen
	State::Focus();

	COORD spawnLocation;

	spawnLocation.X = Config::playAreaSize.X / 4;
	spawnLocation.Y = Config::playAreaSize.Y / 2;
	field.snakes.emplace_back(SnakeFactory::CreatePlayer(
		spawnLocation,
		MovingDirection::North,
		"PLAYER"));

	spawnLocation.X = 35;
	spawnLocation.Y = Config::consoleBufferSize.Y / 4;
	field.snakes.emplace_back(SnakeFactory::CreateMenu(
		spawnLocation,
		std::string("Play game"),
		SnakeType::MenuGotoPlay));

	spawnLocation.Y = Config::consoleBufferSize.Y / 3 + 2;
	field.snakes.emplace_back(SnakeFactory::CreateMenu(
		spawnLocation,
		std::string("Test level"),
		SnakeType::MenuGotoTest));

	spawnLocation.Y = Config::consoleBufferSize.Y / 3 + 4;
	field.snakes.emplace_back(SnakeFactory::CreateMenu(
		spawnLocation,
		std::string("Help"),
		SnakeType::MenuGotoInfo));

	spawnedSnakes = true;
}

void MenuState::Destroy()
{
}

MenuState::MenuState()
	: spawnedSnakes(false)
{
}
