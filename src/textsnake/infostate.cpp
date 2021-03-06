#include "infostate.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "snakefactory.hpp"

void InfoState::Update(unsigned const elapsedMs)
{
	field.Update(elapsedMs);
}

void InfoState::Destroy()
{
}

void InfoState::Focus()
{
	if (spawnedSnakes)
	{
		return;
	}

	// Clear the screen
	State::Focus();

	COORD spawnLocation;
	Color::Color clearColor;

	spawnLocation.X = 10;
	spawnLocation.Y = Config::playAreaSize.Y - 4;
	field.snakes.emplace_back(SnakeFactory::CreatePlayer(
		spawnLocation,
		MovingDirection::East,
		std::string("PLAYER"),
		clearColor));

	spawnLocation.X = 38;
	spawnLocation.Y = Config::playAreaSize.Y - 2;
	field.snakes.emplace_back(SnakeFactory::CreateMenu(
		spawnLocation,
		std::string("Back"),
		SnakeType::MenuGotoMenu));

	spawnedSnakes = true;

	short const controlsBodyColumn = 20;
	short const tipsBodyColumn = 18;
	std::cout
		<< COORD{ 36, 2}
		<< Color::Color(Color::Foreground::WHITE, Color::Background::DARKBLUE)
		<< "Controls"
		<< Color::Color()
		<< COORD{ controlsBodyColumn, 4}
		<< "arrow keys: control the green player snake"
		<< COORD{ controlsBodyColumn, 5 }
		<< "escape:     go back the main menu"
		<< COORD{ controlsBodyColumn, 6 }
		<< "delete:     (un)pause the game (not in menus)"

		<< COORD{ 38, 8 }
		<< Color::Color(Color::Foreground::WHITE, Color::Background::DARKBLUE)
		<< "Tips"
		<< COORD{ tipsBodyColumn, 10 }
		<< Color::Color()
		<< "- Press the arrow key in the reverse direction to"
		<< COORD{ tipsBodyColumn, 11 }
		<< "  instantly turn around"
		<< COORD{ tipsBodyColumn, 12 }
		<< "- Pay attention to the color of your enemies"
		<< COORD{ tipsBodyColumn, 13 }
		<< "- Be careful not to collide with yourself";
}

InfoState::InfoState()
	: spawnedSnakes(false)
{
}
