#include "clustersnake.hpp"
#include "config.hpp"
#include "snakefactory.hpp"
#include <cassert>
#undef min
#undef max

static inline int GetShortestPathDistance(int from, int to, int wrap)
{
	int directDist = std::abs(to - from);
	int indirectDist = wrap - directDist;
	return std::min(directDist, indirectDist);
}
static inline int GetShortestPathDirection(int from, int to, int wrap)
{
	int direct = to - from;
	int directSign = (direct > 0 ? 1 : -1);
	int directDist = std::abs(direct);
	int indirectDist = wrap - direct;
	return directDist <= indirectDist
		? directSign
		: -directSign;
}

static bool filterEnemySnakes(BaseSnake const* snake)
{
	return snake->GetType() != SnakeType::Cluster;
}
static bool filterFriendlySnakes(BaseSnake const* snake)
{
	return snake->GetType() == SnakeType::Cluster;
}

MovingDirection ClusterSnake::CalculateDesiredMovingDirection(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
{
	// keep going straight if there are no other snakes
	if (otherSnakes.size() <= 1)
		return movingDirection;

	// calculate our center of mass
	int cx = 0, cy = 0;
	for (SnakeBlock const block : blocks)
	{
		cx += block.position.X;
		cy += block.position.Y;
	}
	cx /= (int)blocks.size();
	cy /= (int)blocks.size();

	// find an enemy snake within attack distance
	int nearestSnakeDistance = 0;
	COORD nearestSnakeBlock{ 0, 0 };
	BaseSnake const* target = FindNearestSnake(otherSnakes, cx, cy, filterEnemySnakes, nearestSnakeDistance, nearestSnakeBlock);
	if (target && nearestSnakeDistance > Config::clusterAttackDistance)
		target = nullptr;

	// explode
	if (target && nearestSnakeDistance <= Config::clusterExplodeDistance && blocks.size() > 1)
	{
		while (blocks.size() > 1)
		{
			SnakeBlock block = blocks.back();
			blocks.pop_back();
			
			std::unique_ptr<ClusterSnake> newSnake = std::make_unique<ClusterSnake>(std::vector<SnakeBlock>{ block }, clearColor);			
			newSnake->elapsedSinceLastMovement -= elapsedMs; // this snake will get an update during this frame, let's make sure it stays in sync
			newSnake->ChangeDirection(GetOrthogonalMovingDirection(block.direction));

			otherSnakes.emplace_back(std::move(newSnake));
		}
		return movingDirection;
	}

	// update our head colour
	Color::Color desiredHeadColor = (target ? Config::clusterHeadColorAttacking : Config::clusterHeadColorDefault);
	if (headColor.value != desiredHeadColor.value)
	{
		headColor = desiredHeadColor;
		Reverse();
		Reverse();
	}

	// if we didn't find an enemy, try to merge with a friend
	if (!target && GetBlocks().size() < Config::clusterMergeLengthLimit)
	{
		target = FindNearestSnake(otherSnakes, cx, cy, filterFriendlySnakes, nearestSnakeDistance, nearestSnakeBlock);
		if (target && nearestSnakeDistance > Config::clusterAttackDistance)
			target = nullptr;
	}

	// if we didn't find a friend, try to find any enemy
	target = FindNearestSnake(otherSnakes, cx, cy, filterEnemySnakes, nearestSnakeDistance, nearestSnakeBlock);

	// find shortest path to target
	if (target)
	{
		COORD targetBlock = nearestSnakeBlock;
		COORD fieldSize = Config::playAreaSize;
		int dx = GetShortestPathDirection(cx, targetBlock.X, fieldSize.X) * GetShortestPathDistance(cx, targetBlock.X, fieldSize.X);
		int dy = GetShortestPathDirection(cy, targetBlock.Y, fieldSize.Y) * GetShortestPathDistance(cy, targetBlock.Y, fieldSize.Y);
		if (std::abs(dx) >= std::abs(dy))
			return (dx > 0 ? MovingDirection::East : MovingDirection::West);
		else
			return (dy > 0 ? MovingDirection::South : MovingDirection::North);
	}
	return movingDirection;
}

BaseSnake const* ClusterSnake::FindNearestSnake(std::vector<std::unique_ptr<BaseSnake>> const& snakes, int x, int y, SnakeFilter filter, int &outDistance, COORD &outBlock) const
{
	BaseSnake* nearestSnake = nullptr;
	int nearestDistance = std::numeric_limits<int>::max();
	COORD nearestBlock{ 0,0 };
	COORD fieldSize = Config::playAreaSize;
	for (auto const& snake : snakes)
	{
		if (snake.get() == this || !filter(snake.get()))
			continue;
		for (auto const& block : snake->GetBlocks())
		{
			COORD bpos = block.position;
			int distance = GetShortestPathDistance(x, bpos.X, fieldSize.X) + GetShortestPathDistance(y, bpos.Y, fieldSize.Y);
			if (distance < nearestDistance)
			{
				nearestSnake = snake.get();
				nearestDistance = distance;
				nearestBlock = bpos;
			}
		}
	}
	outDistance = nearestDistance;
	outBlock = nearestBlock;
	return nearestSnake;
}

void ClusterSnake::CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
{
	elapsedSinceLastDirectionChange += elapsedMs;
	elapsedSinceLastMovement += elapsedMs;

	if (elapsedSinceLastDirectionChange >= Config::ticksPerClusterChangeOrientation)
	{
		MovingDirection desired = CalculateDesiredMovingDirection(elapsedMs, otherSnakes);
		if (desired != movingDirection)
		{
			elapsedSinceLastDirectionChange = 0;
			ChangeDirection(desired);
		}
	}

	if (elapsedSinceLastMovement >= Config::ticksPerClusterMove)
	{
		elapsedSinceLastMovement = 0;
		nextMove = GetTranslateOffsetByCurrentDirection();
	}
}

SnakeType ClusterSnake::GetType() const
{
	return SnakeType::Cluster;
}

ClusterSnake::ClusterSnake(
	std::vector<SnakeBlock> const& blocks,
	Color::Color const clearColor)
	: BaseSnake(blocks, Config::hunterHeadColor, Config::clusterBodyColor, clearColor),
	elapsedSinceLastDirectionChange(0),
	elapsedSinceLastMovement(0)
{
}
