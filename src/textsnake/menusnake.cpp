#include "menusnake.hpp"
#include "config.hpp"
#include <cassert>

SnakeType MenuSnake::GetType() const
{
  return type;
}

void MenuSnake::CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
{
    elapsedSinceLastTick += elapsedMs;
    if (elapsedSinceLastTick >= Config::ticksPerPlayerMove)
    {
        elapsedSinceLastTick = 0;

        if (Config::GetRandomDouble() <= Config::menuMoveProbability)
        {
            if (driftDirection > 0 && drift >= Config::menuMaxDriftDistance)
            {
                // turn around to drift back
                driftDirection = -1;
                Reverse();
            }
            else
            {
                nextMove = GetTranslateOffsetByCurrentDirection();
                drift += driftDirection;
                if (driftDirection < 0 && drift == 0)
                    driftDirection = 1; // at center, now drifting away
            }
        }
    }
    return;
}

MenuSnake::MenuSnake(
  std::vector<SnakeBlock> const& blocks,
  SnakeType const _type,
  Color::Color clearColor)
  : BaseSnake(
    blocks,
    Config::menuHeadColor,
    Config::menuBodyColor,
    clearColor),
  type(_type),
  elapsedSinceLastTick(0), driftDirection(1), drift(0)
{
    if (Config::GetRandomDouble() < .5)
        Reverse();
}
