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
  COORD const position,
  std::string const& label,
  SnakeType const _type,
  Color::Color clearColor)
  : BaseSnake(
    GenerateLineOfSnakeBlocks(
      position,
      MovingDirection::West,
      label,
      Config::menuHeadColor,
      Config::menuBodyColor),
    Config::menuHeadColor,
    Config::menuBodyColor,
    clearColor),
  type(_type)
{
}
