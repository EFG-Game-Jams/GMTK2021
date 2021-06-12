#include "playingfield.hpp"
#include "config.hpp"
#include "coordops.hpp"
#include <cassert>
#include "randomsnake.hpp"
#include "noaisnake.hpp"
#include "huntersnake.hpp"
#include "statestack.hpp"
#include "gameoverstate.hpp"

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

				if (b.GetType() == SnakeType::Player)
				{
					return CollisionType::PlayerKilled;
				}

				return CollisionType::HeadOnHead;
			}

			if (i == bblocks.size() - 1)
			{
				if (b.GetType() == SnakeType::Player)
				{
					return CollisionType::PlayerKilled;
				}

				if (&a == &b)
				{
					return CollisionType::CircleCreated;
				}

				return CollisionType::HeadOnTail;
			}

			return CollisionType::HeadOnBody;
		}
	}

	return CollisionType::None;
}

std::unique_ptr<BaseSnake> SplitOffTailAt(BaseSnake& snake, COORD collisionPosition)
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

	std::unique_ptr<BaseSnake> newSnake;
	switch (snake.GetType())
	{
	case SnakeType::Random:
	case SnakeType::Player:
		if (Config::GetRandomDouble() < 0.2)
		{
			newSnake = std::make_unique<HunterSnake>(newSnakeBlocks, snake.GetClearColor());
		}
		else
		{
			newSnake = std::make_unique<RandomSnake>(newSnakeBlocks, snake.GetClearColor());
		}
		break;

	case SnakeType::NoAi:
		newSnake = std::make_unique<NoAiSnake>(newSnakeBlocks, snake.GetClearColor());
		break;

	case SnakeType::Hunter:
		if (Config::GetRandomDouble() < 0.1)
		{
			newSnake = std::make_unique<RandomSnake>(newSnakeBlocks, snake.GetClearColor());
		}
		else
		{
			newSnake = std::make_unique<HunterSnake>(newSnakeBlocks, snake.GetClearColor());
		}
		break;
	}

	assert(newSnake.get() != nullptr);

	// Ensure the next move is legal for the new snake
	newSnake->Reverse();
	newSnake->ForceMove();

	return newSnake;
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

				// After this the snakes iteration is invalidated due to insertions and deletions!
				switch (collisionType)
				{
				case CollisionType::HeadOnBody:
				{
					snakes.emplace_back(SplitOffTailAt(**otherSnake, snake->GetNextHeadPosition()));
				}
				break;

				case CollisionType::HeadOnHead:
					(*otherSnake)->Reverse();
					snake->Prepend(**otherSnake);
					snakes.erase(otherSnake);
					break;

				case CollisionType::HeadOnTail:
					snake->Prepend(**otherSnake);
					snakes.erase(otherSnake);
					break;

				case CollisionType::PlayerKilled:
					snake->ForceFreeze();
					(*otherSnake)->ForceFreeze();
					{
						auto & stack = StateStack::GetInstance();
						stack.SchedulePushState(std::make_unique<GameOverState>());
					}
					// Stop doing updates
					return;

				case CollisionType::CircleCreated:
					snake->ForceFreeze();
					break;

				default:
					assert(false);
				}

				hadCollision = true;
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
