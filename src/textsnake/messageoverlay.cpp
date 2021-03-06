#include "cursor.hpp"
#include "messageoverlay.hpp"

void MessageOverlay::RestoreContent()
{
	SMALL_RECT writeRegion;
	writeRegion.Top = lineStartPosition.Y;
	writeRegion.Left = lineStartPosition.X;
	writeRegion.Bottom = lineStartPosition.Y;
	writeRegion.Right = lineStartPosition.X + characterBackup.size();

	WriteConsoleOutput(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&characterBackup[0],
		COORD{ static_cast<SHORT>(characterBackup.size()), 1 },
		COORD{ 0, 0 },
		&writeRegion
	);
}

void MessageOverlay::BackupContent()
{
	characterBackup.resize(maxLineLength);

	SMALL_RECT readRegion;
	readRegion.Top = lineStartPosition.Y;
	readRegion.Left = lineStartPosition.X;
	readRegion.Bottom = lineStartPosition.Y;
	readRegion.Right = lineStartPosition.X + characterBackup.size();

	ReadConsoleOutput(
		GetStdHandle(STD_OUTPUT_HANDLE),
		&characterBackup[0],
		COORD{ static_cast<SHORT>(characterBackup.size()), 1 },
		COORD{ 0, 0 },
		&readRegion
	);
}

void MessageOverlay::DrawMessage(std::string msg, Color::Color const& color) const
{
	if (msg.size() > maxLineLength)
	{
		msg.resize(static_cast<unsigned>(maxLineLength));
	}

	SHORT const x = (maxLineLength / 2) - (msg.size() / 2) + lineStartPosition.X;
	Color::Set(color);
	Cursor::Set({ lineStartPosition.X, lineStartPosition.Y });
	for (SHORT i = lineStartPosition.X; i < x; ++i)
		std::cout << ' ';
	std::cout << msg;
	for (SHORT i = x + msg.size(); i < lineStartPosition.X + maxLineLength; ++i)
		std::cout << ' ';
}

bool MessageOverlay::IsOverlay() const
{
	return true;
}

void MessageOverlay::Focus()
{
	BackupContent();
	DrawMessage(message, color);
}

void MessageOverlay::Destroy()
{
	RestoreContent();
}

MessageOverlay::MessageOverlay(COORD const _lineStartPosition,
	SHORT const _maxLineLength,
	std::string const& _message,
	Color::Color const& _color)
	: lineStartPosition(_lineStartPosition),
	maxLineLength(_maxLineLength),
	message(_message),
	color(_color)
{
}
