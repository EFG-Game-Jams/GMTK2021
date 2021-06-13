#include "levelstate.hpp"
#include "snakefactory.hpp"
#include <cassert>
#include "config.hpp"
#include "scoreoverlay.hpp"
#include "cursor.hpp"
#include "messagebuffer.hpp"

void LevelState::LoadLevel()
{
	// Clear the screen
	std::cout << COORD{ 0,0 } << Color::Color(); // Black
	std::size_t const limit = Config::playAreaSize.X * Config::playAreaSize.Y;
	for (std::size_t i = 0; i < limit; ++i)
	{
		std::cout << ' ';
	}

	field.snakes.clear();

	switch (level)
	{
	case 0:
		field.allowNoAi = true;
		field.allowRandom = false;
		field.allowHunter = false;

		field.snakes.emplace_back(SnakeFactory::CreatePlayer(
			COORD{ Config::playAreaSize.X / 2, Config::playAreaSize.Y / 2 },
			MovingDirection::North,
			"PLAYER"));

		field.snakes.emplace_back(SnakeFactory::CreateNoAi(
			COORD{ Config::playAreaSize.X / 5, Config::playAreaSize.Y / 2 },
			MovingDirection::East,
			"ONEWAY"));
		break;

	case 1:
		field.allowNoAi = true;
		field.allowRandom = true;
		field.allowHunter = false;

		field.snakes.emplace_back(SnakeFactory::CreatePlayer(
			COORD{ Config::playAreaSize.X / 2, Config::playAreaSize.Y / 2 },
			MovingDirection::North,
			"PLAYER"));

		field.snakes.emplace_back(SnakeFactory::CreateRandom(
			COORD{ Config::playAreaSize.X / 5, Config::playAreaSize.Y / 2 },
			MovingDirection::East,
			"RANDOM"));

		field.snakes.emplace_back(SnakeFactory::CreateRandom(
			COORD{ Config::playAreaSize.X - 4, Config::playAreaSize.Y / 4 },
			MovingDirection::South,
			"RANDOM"));
		break;

	case 2:
		field.allowNoAi = true;
		field.allowRandom = true;
		field.allowHunter = false;

		field.snakes.emplace_back(SnakeFactory::CreatePlayer(
			COORD{ Config::playAreaSize.X / 2, Config::playAreaSize.Y / 2 },
			MovingDirection::North,
			"PLAYER"));

		field.snakes.emplace_back(SnakeFactory::CreateRandom(
			COORD{ Config::playAreaSize.X / 5, Config::playAreaSize.Y / 2 },
			MovingDirection::East,
			"VERY LONG SNAKE"));
		break;

	case 3:
		field.allowNoAi = false;
		field.allowRandom = true;
		field.allowHunter = true;

		field.snakes.emplace_back(SnakeFactory::CreatePlayer(
			COORD{ Config::playAreaSize.X / 2, Config::playAreaSize.Y / 2 },
			MovingDirection::North,
			"PLAYER"));

		field.snakes.emplace_back(SnakeFactory::CreateRandom(
			COORD{ Config::playAreaSize.X - 3, Config::playAreaSize.Y / 4 },
			MovingDirection::East,
			"ENEMY"));

		field.snakes.emplace_back(SnakeFactory::CreateRandom(
			COORD{ 2, 2 },
			MovingDirection::West,
			"ENEMY"));
		break;

	default:
		assert(false); // Win!
		return;
	}

	assert(field.snakes[0]->GetType() == SnakeType::Player);
	assert(field.allowHunter || field.allowNoAi || field.allowRandom);

	MessageBuffer::Publish(MessageType::LevelLoaded, level);
}

void LevelState::Update(unsigned const elapsedMs)
{
	auto const reloadRequested = MessageBuffer::Consume(lastConsumeTime, MessageType::ReloadLevel).size() > 0;
	lastConsumeTime = std::chrono::steady_clock::now();
	if (reloadRequested)
	{
		LoadLevel();
		return;
	}

	field.Update(elapsedMs);

	if (field.snakes.size() == 1 && field.snakes[0]->GetType() == SnakeType::Player)
	{
		++level;
		LoadLevel();
		return;
	}
}

void LevelState::Destroy()
{
}

void LevelState::Focus()
{
	if (loaded)
	{
		return;
	}

	LoadLevel();

	StateStack::GetInstance().PushState(std::make_unique<ScoreOverlay>());

	loaded = true;
}

LevelState::LevelState(int _level)
	: level(_level),
	loaded(false),
	lastConsumeTime(std::chrono::steady_clock::now())
{
}
