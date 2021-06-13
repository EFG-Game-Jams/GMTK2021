#include "menusnake.hpp"
#include "config.hpp"
#include <cassert>

SnakeType MenuSnake::GetType() const
{
  return type;
}

void MenuSnake::CalculateNextMove(unsigned const elapsedMs, std::vector<std::unique_ptr<BaseSnake>>& otherSnakes)
{
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
  type(_type)
{
}
