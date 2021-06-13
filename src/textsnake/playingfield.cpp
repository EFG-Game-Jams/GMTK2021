#include "playingfield.hpp"
#include "config.hpp"
#include "coordops.hpp"
#include <cassert>
#include "randomsnake.hpp"
#include "noaisnake.hpp"
#include "huntersnake.hpp"
#include "soundeffect.hpp"
#include "messagebuffer.hpp"

CollisionType PlayingField::Collides(BaseSnake const& a, BaseSnake const& b) const
{
	auto const ahead = a.GetNextHeadPosition();
	auto const& bblocks = b.GetBlocks();
	for (std::size_t i = 0; i < bblocks.size(); ++i)
	{
		if (bblocks[i].position == ahead)
		{
			if (i == 0)
			{
				// Self head intersection is not possible
				if (&a == &b)
				{
					return CollisionType::None;
				}

				return CollisionType::HeadOnHead;
			}

			if (i == bblocks.size() - 1)
			{
				if (&a == &b)
				{
					if (a.GetSize() < 5)
					{
						// Self intersect needs at least length 5 to happen
						return CollisionType::None;
					}

					return CollisionType::CircleCreated;
				}

				return CollisionType::HeadOnTail;
			}

			if (&a == &b && a.GetSize() < 5)
			{
				// Self intersect needs at least length 5 to happen
				return CollisionType::None;
			}

			return CollisionType::HeadOnBody;
		}
	}

	return CollisionType::None;
}

SnakeType PlayingField::GetTailSnakeType(SnakeType const sourceType)
{
	// ADD new snake types here
	double randomChance = 0.0;
	double noAiChance = 0.0;
	double hunterChance = 0.0;

	// ADD new snake types here
	switch (sourceType)
	{
	case SnakeType::Player:
		randomChance = 20.0;
		noAiChance = 5.0;
		hunterChance = 1.0;
		break;

	case SnakeType::Random:
		randomChance = 20.0;
		noAiChance = 5.0;
		hunterChance = 1.0;
		break;

	case SnakeType::NoAi:
		noAiChance = 20.0;
		randomChance = 5.0;
		break;

	case SnakeType::Hunter:
		hunterChance = 20.0;
		randomChance = 5.0;
		break;

	default:
		assert(false);
		break;
	}

	// ADD new snake types here
	randomChance *= allowRandom ? 1.0 : 0.0;
	noAiChance *= allowNoAi ? 1.0 : 0.0;
	hunterChance *= allowHunter ? 1.0 : 0.0;

	// ADD new snake types here
	double const cumulative = randomChance + noAiChance + hunterChance;

	// ADD new snake types here
	randomChance /= cumulative;
	noAiChance /= cumulative;
	hunterChance /= cumulative;

	double total = randomChance;
	if (Config::GetRandomDouble() < total)
	{
		return SnakeType::Random;
	}

	total += noAiChance;
	if (Config::GetRandomDouble() < total)
	{
		return SnakeType::NoAi;
	}

	total += hunterChance;
	if (Config::GetRandomDouble() < total)
	{
		return SnakeType::Hunter;
	}

	// ADD new snake types here

	assert(false);
}

std::unique_ptr<BaseSnake> PlayingField::SplitOffTailAt(BaseSnake& snake, COORD collisionPosition)
{
	auto const& blocks = snake.GetBlocks();
	std::vector<SnakeBlock> newSnakeBlocks;
	bool isNewSnakeBit = false;
	for (std::size_t i = 0; i < blocks.size(); ++i)
	{
		if (collisionPosition == blocks[i].position)
		{
			isNewSnakeBit = true;
		}

		if (isNewSnakeBit)
		{
			newSnakeBlocks.push_back(blocks[i]);
		}
	}

	assert(newSnakeBlocks.size() != 0);
	assert(newSnakeBlocks.size() != blocks.size());

	// Remove new snake letters from existing snake
	snake.Trim(blocks.size() - newSnakeBlocks.size());

	auto const newSnakeType = GetTailSnakeType(snake.GetType());
	assert(newSnakeType != SnakeType::Player);
	std::unique_ptr<BaseSnake> newSnake;
	switch (newSnakeType)
	{
	case SnakeType::Random:
		newSnake = std::make_unique<RandomSnake>(newSnakeBlocks, snake.GetClearColor());
		break;

	case SnakeType::NoAi:
		newSnake = std::make_unique<NoAiSnake>(newSnakeBlocks, snake.GetClearColor());
		break;

	case SnakeType::Hunter:
		newSnake = std::make_unique<HunterSnake>(newSnakeBlocks, snake.GetClearColor());
		break;
	}

	assert(newSnake.get() != nullptr);

	// Ensure the next move is legal for the new snake
	newSnake->Reverse();
	newSnake->ForceMove();

	return newSnake;
}

bool PlayingField::HandlePlayerDeath(BaseSnake &deadSnake, BaseSnake &otherSnake) const
{
	if (deadSnake.GetType() != SnakeType::Player)
		return false;

	deadSnake.ForceFreeze();
	otherSnake.ForceFreeze();

	MessageBuffer::Publish(MessageType::PlayerKilled);

	PlaySoundEffect(SoundEffect::TWINKLEBAD1);
	
	// Stop doing updates
	return true;
}

void PlayingField::UpdateCollisions()
{
	bool hadCollision = false;
	do
	{
		hadCollision = false;

		for (auto& snake : snakes)
		{
			for (auto otherSnake = snakes.begin(); otherSnake != snakes.end(); ++otherSnake)
			{
				auto const collisionType = Collides(*snake, **otherSnake);
				if (collisionType == CollisionType::None)
				{
					continue;
				}

				hadCollision = true;

				// After this the snakes iteration is invalidated due to insertions and deletions!
				switch (collisionType)
				{
				case CollisionType::HeadOnBody:
					if (
						(*otherSnake)->GetType() != SnakeType::Player ||
						snake->GetType() == SnakeType::Player ||
						snake->GetType() == SnakeType::Hunter)
					{
						if (snake->GetType() == SnakeType::Player)
						{
							MessageBuffer::Publish(MessageType::ScoreGained, Config::scoreSplit);
						}

						snakes.emplace_back(SplitOffTailAt(**otherSnake, snake->GetNextHeadPosition()));
						PlaySoundEffect(SoundEffect::BAD1);
					}
					else
					{
						snake->ForceFreeze();
						hadCollision = false;
					}
				break;

				case CollisionType::HeadOnHead:
					if (snake->GetSize() >= (*otherSnake)->GetSize())
					{
						if (HandlePlayerDeath(**otherSnake, *snake))
							return;

						if (snake->GetType() == SnakeType::Player)
							MessageBuffer::Publish(MessageType::ScoreGained, Config::scoreConsumeHeadBase + Config::scoreConsumeHeadBlock * (*otherSnake)->GetBlocks().size());

						(*otherSnake)->Reverse();
						snake->Prepend(**otherSnake);
						snakes.erase(otherSnake);
						PlaySoundEffect(SoundEffect::GOOD1);
					}
					else
					{
						snake->ForceFreeze();
						hadCollision = false;
					}
					break;

				case CollisionType::HeadOnTail:
					if (snake->GetSize() >= (*otherSnake)->GetSize())
					{
						if (HandlePlayerDeath(**otherSnake, *snake))
							return;

						if (snake->GetType() == SnakeType::Player)
							MessageBuffer::Publish(MessageType::ScoreGained, Config::scoreConsumeTailBase + Config::scoreConsumeTailBlock * (*otherSnake)->GetBlocks().size());

						snake->Prepend(**otherSnake);
						snakes.erase(otherSnake);
						PlaySoundEffect(SoundEffect::GOOD1);
					}
					else
					{
						snake->ForceFreeze();
						hadCollision = false;
					}
					break;

				/*case CollisionType::PlayerKilled:
					snake->ForceFreeze();
					(*otherSnake)->ForceFreeze();
					{
						auto & stack = StateStack::GetInstance();
						stack.PushState(std::make_unique<GameOverOverlay>());
					}
					PlaySoundEffect(SoundEffect::TWINKLEBAD1);
					// Stop doing updates
					return;*/

				case CollisionType::CircleCreated:
					if (HandlePlayerDeath(*snake, *snake))
						return;
					snake->ForceFreeze();
					hadCollision = false;
					break;

				default:
					assert(false);
				}

				break;
			}

			if (hadCollision)
			{
				break;
			}
		}
	} while (hadCollision);
}

void PlayingField::Update(unsigned const elapsedMs)
{
	for (auto& snake : snakes)
	{
		snake->CalculateNextMove(elapsedMs, snakes);
	}

	UpdateCollisions();

	for (auto& snake : snakes)
	{
		snake->Update();
	}
}

PlayingField::PlayingField(
	bool _allowNoAi,
	bool _allowRandom,
	bool _allowHunter)
	: allowNoAi(_allowNoAi),
	allowRandom(_allowRandom),
	allowHunter(_allowHunter)
{
}
