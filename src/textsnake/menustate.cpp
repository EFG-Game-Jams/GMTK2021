#include "config.hpp"
#include "menustate.hpp"
#include "playersnake.hpp"
#include "menusnake.hpp"

void MenuState::Update(unsigned const elapsedMs)
{
	field.Update(elapsedMs);
}

void MenuState::Awake()
{
	if (spawnedSnakes)
	{
		return;
	}

	COORD spawnLocation;
	Color::Color clearColor;

	spawnLocation.X = Config::consoleBufferSize.X / 4;
	spawnLocation.Y = Config::consoleBufferSize.Y / 2;
	field.snakes.emplace_back(std::make_unique<PlayerSnake>(
		spawnLocation,
		std::string("PLAYER"),
		clearColor));

	spawnLocation.X = 35;
	spawnLocation.Y = Config::consoleBufferSize.Y / 4;
	field.snakes.emplace_back(std::make_unique<MenuSnake>(
		spawnLocation,
		std::string("Play game"),
		SnakeType::MenuGotoPlay,
		clearColor));

	spawnLocation.Y = Config::consoleBufferSize.Y / 3 + 2;
	field.snakes.emplace_back(std::make_unique<MenuSnake>(
		spawnLocation,
		std::string("Test level"),
		SnakeType::MenuGotoTest,
		clearColor));

	spawnLocation.Y = Config::consoleBufferSize.Y / 3 + 4;
	field.snakes.emplace_back(std::make_unique<MenuSnake>(
		spawnLocation,
		std::string("Help"),
		SnakeType::MenuGotoInfo,
		clearColor));

	spawnedSnakes = true;
}

MenuState::MenuState()
	: spawnedSnakes(false)
{
}

MenuState::~MenuState()
{
}
