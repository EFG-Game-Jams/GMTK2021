#include "player.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include "color.hpp"

void Player::DrawPlayer() const
{
	std::cout << COORD{ static_cast<short>(x), static_cast<short>(y) } << Color::Color() << 'P';
}

void Player::HandleInput(UserInput const& input)
{
	short oldx = x, oldy = y;

	if (input.WasActionPressed(PlayerActions::MoveUp))
	{
		--y;
	}
	else if (input.WasActionPressed(PlayerActions::MoveDown))
	{
		++y;
	}

	if (input.WasActionPressed(PlayerActions::MoveRight))
	{
		++x;
	}
	else if (input.WasActionPressed(PlayerActions::MoveLeft))
	{
		--x;
	}

	if (x < 0) {
		x = Config::consoleBufferSize.X - 1;
	}
	else if (x >= Config::consoleBufferSize.X)
	{
		x = 0;
	}

	if (y < 0) {
		y = Config::consoleBufferSize.Y - 1;
	}
	else if (y >= Config::consoleBufferSize.Y)
	{
		y = 0;
	}

	std::cout << COORD{ static_cast<short>(oldx), static_cast<short>(oldy) } << Color::Color() << ' ';
	DrawPlayer();
}

Player::Player(int const spawnX, int const spawnY)
	: x(spawnX), y(spawnY)
{
	DrawPlayer();
}
