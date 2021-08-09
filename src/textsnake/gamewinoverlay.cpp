#include "gamewinoverlay.hpp"
#include "cursor.hpp"
#include "snakefactory.hpp"
#include "config.hpp"
#include <sstream>
#include "globalgamestate.hpp"

void GameWinOverlay::Update(unsigned const elapsedMs)
{
}

void GameWinOverlay::Focus()
{
  MessageOverlay::Focus();
}

void GameWinOverlay::Destroy()
{
}

GameWinOverlay::GameWinOverlay()
  : MessageOverlay(
    COORD{ 0, Config::consoleBufferSize.Y / 2 - 1 },
    Config::consoleBufferSize.X,
    "",
    Color::Color(Color::Foreground::WHITE, Color::Background::DARKGREEN))
{
  auto score = GlobalGameState::Get().GetPlayerScore();

  std::stringstream ss;
  ss << "You won with a score of " << score << "!";
  message = ss.str();
}
