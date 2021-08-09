#include "config.hpp"
#include "userinput.hpp"
#include "statestack.hpp"
#include "gameoveroverlay.hpp"
#include "menustate.hpp"
#include "snakefactory.hpp"
#include "cursor.hpp"
#include "statestack.hpp"
#include "globalgamestate.hpp"

void GameOverOverlay::LoadMenu()
{
	// Clear the screen
	std::cout << COORD{ 0,0 } << Color::Color(); // Black
	std::size_t const limit = Config::playAreaSize.X * Config::playAreaSize.Y;
	for (std::size_t i = 0; i < limit; ++i)
	{
		std::cout << ' ';
	}

	COORD spawnLocation;

	spawnLocation.X = Config::playAreaSize.X / 4;
	spawnLocation.Y = Config::playAreaSize.Y - 5;
	field.snakes.emplace_back(SnakeFactory::CreatePlayer(
		spawnLocation,
		MovingDirection::North,
		"PLAYER"));

	spawnLocation.X = 20;
	spawnLocation.Y = Config::consoleBufferSize.Y / 2 - 1;
	field.snakes.emplace_back(SnakeFactory::CreateMenu(
		spawnLocation,
		std::string("Retry"),
		SnakeType::MenuRequestReload));

	spawnLocation.X = 50;
	field.snakes.emplace_back(SnakeFactory::CreateMenu(
		spawnLocation,
		std::string("Exit"),
		SnakeType::MenuGotoMenu));

	menuLoaded = true;
}

void GameOverOverlay::Update(unsigned const elapsedMs)
{
	elapsedTotal += elapsedMs;
	auto& evHandler = UserInput::GetInstance();

	if (!menuLoaded && (evHandler.WasActionReleased(PlayerActions::Action) || elapsedTotal > 2000))
	{
		LoadMenu();
	}

	if (menuLoaded)
	{
		field.Update(elapsedMs);
	}

	// DANGEROUS ASSUMPTION: on reload this overlay needs to go, we just pop the last
	// state expecting it to be ourselves
	if (GlobalGameState::Get().IsLevelReloadRequested())
	{
		StateStack::GetInstance().PopState();
		return;
	}
}

GameOverOverlay::GameOverOverlay()
	: MessageOverlay(
		COORD{0, Config::consoleBufferSize.Y / 2 - 1},
		Config::consoleBufferSize.X,
		"Game Over!",
		Color::Color(Color::Foreground::WHITE, Color::Background::DARKRED)),
	elapsedTotal(0),
	menuLoaded(false)
{
}
