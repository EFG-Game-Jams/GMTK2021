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
	
	virtual void UpdateCollisions();

public:
	std::vector<std::unique_ptr<BaseSnake>> snakes;

	void Update(unsigned const elapsedMs);
};
