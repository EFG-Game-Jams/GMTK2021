#include "playingfield.hpp"
#include "config.hpp"
#include "coordops.hpp"
#include <cassert>
#include "randomsnake.hpp"
#include "noaisnake.hpp"

enum class CollisionType
{
	None,
	Fatal,
	HeadOnBody,
	HeadOnHead,
	HeadOnTail
};

CollisionType Collides(BaseSnake const& a, BaseSnake const& b)
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
					return CollisionType::Fatal;
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
	std::string newSnakeLetters;
	bool isNewSnakeBit = false;
	for (std::size_t i = 0; i < blocks.size(); ++i)
	{
		if (collisionPosition == blocks[i].position)
		{
			isNewSnakeBit = true;
		}

		if (isNewSnakeBit)
		{
			newSnakeLetters += blocks[i].character;
		}
	}

	assert(newSnakeLetters.size() != 0);
	assert(newSnakeLetters.size() != blocks.size());

	auto const newSnakeMovingDirection = blocks[blocks.size() - 1].direction;
	// Remove new snake letters from existing snake
	snake.Trim(blocks.size() - newSnakeLetters.size());

	std::unique_ptr<BaseSnake> newSnake;
	switch (snake.GetType())
	{
	case SnakeType::Random:
	case SnakeType::Player:
		newSnake = std::make_unique<RandomSnake>(
			newSnakeMovingDirection,
			collisionPosition,
			newSnakeLetters,
			snake.GetClearColor());

	case SnakeType::NoAi:
		newSnake = std::make_unique<NoAiSnake>(
			newSnakeMovingDirection,
			collisionPosition,
			newSnakeLetters,
			snake.GetClearColor());
	}

	assert(newSnake.get() != nullptr);

	// Ensure the next move is legal for the new snake
	newSnake->Reverse();
	newSnake->ForceMove();

	return newSnake;
}

void PlayingField::Update(unsigned const elapsedMs)
{
	for (auto& snake : snakes)
	{
		snake->CalculateNextMove(elapsedMs);
	}

	bool hadCollision = false;
	do
	{
		hadCollision = false;

		for (auto & snake : snakes)
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

				case CollisionType::Fatal:
					if (snake->GetType() == SnakeType::Player)
					{
						assert(false);
					}
					else
					{
						snake->ForceFreeze();
					}
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

	for (auto& snake : snakes)
	{
		snake->Update();
	}
}