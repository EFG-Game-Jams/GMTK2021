#include "snakefactory.hpp"
#include "config.hpp"

std::unique_ptr<HunterSnake> SnakeFactory::CreateHunter(COORD const position, MovingDirection const orientation, std::string const & letters, Color::Color const clearColor)
{
	return std::make_unique<HunterSnake>(
		GenerateLineOfSnakeBlocks(
			position,
			orientation,
			letters,
			Config::hunterHeadColor,
			Config::hunterBodyColor),
		clearColor);
}

std::unique_ptr<PlayerSnake> SnakeFactory::CreatePlayer(COORD const position, MovingDirection const orientation, std::string const & letters, Color::Color const clearColor)
{
	return std::make_unique<PlayerSnake>(
		GenerateLineOfSnakeBlocks(
			position,
			orientation,
			letters,
			Config::playerHeadColor,
			Config::playerBodyColor),
		clearColor);
}

std::unique_ptr<NoAiSnake> SnakeFactory::CreateNoAi(COORD const position, MovingDirection const orientation, std::string const & letters, Color::Color const clearColor)
{
	return std::make_unique<NoAiSnake>(
		GenerateLineOfSnakeBlocks(
			position,
			orientation,
			letters,
			Config::dumbHeadColor,
			Config::dumbBodyColor),
		clearColor);
}

std::unique_ptr<RandomSnake> SnakeFactory::CreateRandom(COORD const position, MovingDirection const orientation, std::string const & letters, Color::Color const clearColor)
{
	return std::make_unique<RandomSnake>(
		GenerateLineOfSnakeBlocks(
			position,
			orientation,
			letters,
			Config::dumbHeadColor,
			Config::dumbBodyColor),
		clearColor);
}

std::unique_ptr<MenuSnake> SnakeFactory::CreateMenu(COORD const position, std::string const& letters, SnakeType const type)
{
	return std::make_unique<MenuSnake>(
		GenerateLineOfSnakeBlocks(
			position,
			MovingDirection::West,
			letters,
			Config::menuHeadColor,
			Config::menuBodyColor),
		type,
		Color::Color());
}
