#pragma once
#include "basesnake.hpp"
#include <memory>
#include <vector>
#include "collisiontype.hpp"

struct PlayingField
{
protected:
	CollisionType Collides(BaseSnake const& a, BaseSnake const& b) const;
	
	bool HandlePlayerDeath(BaseSnake& deadSnake, BaseSnake& otherSnake) const;
	
	SnakeType GetTailSnakeType(SnakeType const sourceType);
	std::unique_ptr<BaseSnake> SplitOffTailAt(BaseSnake& snake, COORD collisionPosition);
	virtual void UpdateCollisions();

public:
	bool allowNoAi;
	bool allowRandom;
	bool allowHunter;

	std::vector<std::unique_ptr<BaseSnake>> snakes;

	void Update(unsigned const elapsedMs);

	PlayingField(
		bool allowNoAi = true,
		bool allowRandom = true,
		bool allowHunter = true);
};
