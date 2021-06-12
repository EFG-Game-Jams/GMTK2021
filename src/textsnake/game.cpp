#include "config.hpp"
#include "game.hpp"
#include "menustate.hpp"
#include <thread>
#include <Windows.h>

void Game::Run(unsigned const targetFrameTime)
{
	StateStack& stateStack = StateStack::GetInstance();
	stateStack.PushState(std::make_unique<MenuState>());

	UserInput& evHandler = UserInput::GetInstance();
	while (stateStack.StateCount())
	{
		auto const start = std::chrono::steady_clock::now();

		evHandler.Update();
		stateStack.GetTopState()->Update(targetFrameTime);

		auto const sleepTime = targetFrameTime - std::chrono::duration_cast<std::chrono::milliseconds>(start - std::chrono::steady_clock::now()).count();
		if (sleepTime > 0 && sleepTime <= targetFrameTime)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
		}
	}
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

	SetConsoleTitle(L"Console Test");
}

Game::Game()
{
	// Setup the console screen
	HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleWindowSize(stdoutHandle, Config::consoleBufferSize.X, Config::consoleBufferSize.Y);

	// Turn off the cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(stdoutHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(stdoutHandle, &cursorInfo);

	// Clear the console
	std::cout << Color::Color(); // Black
	std::size_t const limit = Config::consoleBufferSize.X * Config::consoleBufferSize.Y;
	for (std::size_t i = 0; i < limit; ++i)
	{
		std::cout << ' ';
	}
}

Game::~Game()
{
}
