#include "config.hpp"
#include "game.hpp"
#include "menustate.hpp"
#include "levelstate.hpp"
#include <thread>
#include <Windows.h>
#include <cassert>

void Game::Reset(int level)
{
	stateStack.Clear();

	if (level < 0)
	{
		stateStack.PushState(std::make_unique<MenuState>());
	}
	else
	{
		stateStack.PushState(std::make_unique<LevelState>(level));
	}
}

void Game::HandleInput()
{
	// TODO remove this cheap reset? It is also mentioned in the info game state!
	if (userInput.WasActionReleased(PlayerActions::Escape))
	{
		stateStack.PushState(std::make_unique<MenuState>());
	}
}

void Game::Run(long long const targetFrameTime, int level)
{
	Reset(level);

	do
	{
		auto const start = std::chrono::steady_clock::now();

		userInput.Update();
		HandleInput();

		stateStack.Update(targetFrameTime);

		auto const executionLength = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
		auto const sleepTime = targetFrameTime - executionLength;
		if (sleepTime > 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		}
	} while (stateStack.StateCount());
}

void SetConsoleWindowSize(HANDLE conout, SHORT cols, SHORT rows)
{
	CONSOLE_SCREEN_BUFFER_INFOEX sbInfoEx;
	sbInfoEx.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(conout, &sbInfoEx);
	sbInfoEx.dwSize.X = cols;
	sbInfoEx.dwSize.Y = rows;
	sbInfoEx.srWindow = { 0, 0, cols, rows };
	sbInfoEx.dwMaximumWindowSize = { cols, rows };
	SetConsoleScreenBufferInfoEx(conout, &sbInfoEx);

	DWORD mode;
	GetConsoleMode(conout, &mode);
	mode &= ~ENABLE_WRAP_AT_EOL_OUTPUT;
	SetConsoleMode(conout, mode);

	SetConsoleTitle(L"Text Snake");
}

Game::Game()
	: stateStack(StateStack::GetInstance()),
	userInput(UserInput::GetInstance())
{
	// Setup the console screen
	HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleWindowSize(stdoutHandle, Config::consoleBufferSize.X, Config::consoleBufferSize.Y);

	// Turn off the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(stdoutHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(stdoutHandle, &cursorInfo);

	// Setup font
	CONSOLE_FONT_INFOEX cfi;
	memset(&cfi, 0, sizeof(CONSOLE_FONT_INFOEX));
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	if (GetCurrentConsoleFontEx(stdoutHandle, FALSE, &cfi))
	{
		COORD size = GetConsoleFontSize(stdoutHandle, cfi.nFont);
		cfi.dwFontSize.X = 20;
		cfi.dwFontSize.Y = 20;

		SetCurrentConsoleFontEx(stdoutHandle, FALSE, &cfi);
	}
	else
	{
		auto error = GetLastError();
		std::cout << error;
	}
}

Game::~Game()
{
}
