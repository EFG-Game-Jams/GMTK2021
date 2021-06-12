#include "config.hpp"
#include "game.hpp"
#include "menustate.hpp"
#include <thread>
#include <Windows.h>

void Game::Reset()
{
	// Clear the console
	std::cout << Color::Color(); // Black
	std::size_t const limit = Config::consoleBufferSize.X * Config::consoleBufferSize.Y;
	for (std::size_t i = 0; i < limit; ++i)
	{
		std::cout << ' ';
	}

	stateStack.Clear();
	stateStack.PushState(std::make_unique<MenuState>());
}

void Game::HandleInput()
{
	// TODO remove this cheap reset
	if (userInput.WasActionReleased(PlayerActions::Escape))
	{
		Reset();
	}
}

void Game::Run(long long const targetFrameTime)
{
	Reset();

	while (stateStack.StateCount())
	{
		auto const start = std::chrono::steady_clock::now();

		userInput.Update();
		HandleInput();

		stateStack.GetTopState()->Update(targetFrameTime);

		auto const executionLength = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
		auto const sleepTime = targetFrameTime - executionLength;
		if (sleepTime > 0)
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
}

Game::~Game()
{
}
