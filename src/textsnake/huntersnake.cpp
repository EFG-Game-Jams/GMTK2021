#include "huntersnake.hpp"
#include "config.hpp"
#include "statestack.hpp"
#include "playingfield.hpp"
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

MovingDirection HunterSnake::CalculateDesiredMovingDirection(std::vector<std::unique_ptr<BaseSnake>> const& otherSnakes)
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

	// find snake whose head is nearest to our center of mass
	COORD fieldSize = Config::consoleBufferSize;
	BaseSnake* nearestSnake = nullptr;
	int nearestDistance = std::numeric_limits<int>::max();
	for (auto const& snake : otherSnakes)
	{
		if (snake.get() == this)
			continue;
		COORD headPos = snake->GetHead().position;
		int distance = GetShortestPathDistance(cx, headPos.X, fieldSize.X) + GetShortestPathDistance(cy, headPos.Y, fieldSize.Y);
		if (distance < nearestDistance)
		{
			nearestSnake = snake.get();
			nearestDistance = distance;
		}
	}

	// find shortest path direction
	assert(nearestSnake);
	COORD target = nearestSnake->GetHead().position;
	int dx = GetShortestPathDirection(cx, target.X, fieldSize.X) * GetShortestPathDistance(cx, target.X, fieldSize.X);
	int dy = GetShortestPathDirection(cy, target.Y, fieldSize.Y) * GetShortestPathDistance(cy, target.Y, fieldSize.Y);
	if (std::abs(dx) >= std::abs(dy))
		return (dx > 0 ? MovingDirection::East : MovingDirection::West);
	else
		return (dy > 0 ? MovingDirection::South : MovingDirection::North);
}

void HunterSnake::CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
{
	elapsedSinceLastDirectionChange += elapsedMs;
	elapsedSinceLastMovement += elapsedMs;

	if (elapsedSinceLastDirectionChange >= Config::ticksPerHunterChangeOrientation)
	{
		MovingDirection desired = CalculateDesiredMovingDirection(otherSnakes);
		if (desired != movingDirection)
		{
			elapsedSinceLastDirectionChange = 0;
			ChangeDirection(desired);
		}
	}

	if (elapsedSinceLastMovement >= Config::ticksPerHunterMove)
	{
		elapsedSinceLastMovement = 0;
		nextMove = GetTranslateOffsetByCurrentDirection();
	}
}

SnakeType HunterSnake::GetType() const
{
	return SnakeType::Hunter;
}

HunterSnake::HunterSnake(
	std::vector<SnakeBlock> const& blocks,
	Color::Color const clearColor)
	: BaseSnake(blocks, Config::hunterHeadColor, Config::hunterBodyColor, clearColor),
	elapsedSinceLastDirectionChange(0),
	elapsedSinceLastMovement(0)
{
}
