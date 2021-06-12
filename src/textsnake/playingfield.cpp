#include "playingfield.hpp"
#include "config.hpp"

enum class CollisionType
{
	None,
	HeadOnBody,
	HeadOnHead,
	HeadOnTail
};

CollisionType Collides(BaseSnake const& a, BaseSnake const& b)
{
	return CollisionType::None;
}

void PlayingField::Update(unsigned const elapsedMs)
{
	for (auto& snake : snakes)
	{
		snake->CalculateNextMove(elapsedMs);
	}

	for (auto& snake : snakes)
	{
		for (auto& otherSnake : snakes)
		{ /*
			if (Collides(*snake, *otherSnake))
			{

			}*/
		}
	}

	for (auto& snake : snakes)
	{
		snake->Update();
	}
}

