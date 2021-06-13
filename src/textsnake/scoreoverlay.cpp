#include "scoreoverlay.hpp"
#include "messagebuffer.hpp"
#include "statestack.hpp"
#include "gameoveroverlay.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include <cstdio>

void ScoreOverlay::DrawScore() const
{
	std::cout << COORD{ 1, Config::consoleBufferSize.Y - 1 } << Config::scoreBoardColor;
	std::printf("SCORE: %04d", score < 10000 ? score : 9999);
}

void ScoreOverlay::DrawPause() const
{
	std::cout << COORD{ Config::consoleBufferSize.X - 13, Config::consoleBufferSize.Y - 1 } << Config::scoreBoardColor;
	if (!isPaused)
	{
		std::cout << "            ";
	}
	else
	{
		std::cout << "PAUSED (DEL)";
	}
}

bool ScoreOverlay::IsOverlay() const
{
	return true;
}

bool ScoreOverlay::UpdateBelow() const
{
	return !isPaused;
}

void ScoreOverlay::Update(unsigned const elapsedMs)
{
	auto messages = MessageBuffer::Consume(lastConsumeTime);
	lastConsumeTime = std::chrono::steady_clock::now();

	for (auto& message : messages)
	{
		switch (message->GetType())
		{
		case MessageType::TogglePause:
			isPaused = !isPaused;
			DrawPause();
			break;

		case MessageType::PlayerKilled:
			isPaused = true;
			StateStack::GetInstance().PushState(std::make_unique<GameOverOverlay>());
			break;

		case MessageType::LevelComplete:
			isPaused = true;
			break;

		case MessageType::ScoreGained:
			score += message->GetPayload();
			DrawScore();
			break;

		default:
			break;
		}
	}

	auto& userInput = UserInput::GetInstance();
	if (userInput.WasActionPressed(PlayerActions::Pause))
	{
		isPaused = !isPaused;
		return;
	}
}

void ScoreOverlay::Focus()
{
	std::cout << COORD{ 0, Config::consoleBufferSize.Y - 1 } << Config::scoreBoardColor;
	for (std::size_t i = 0; i < Config::consoleBufferSize.X; ++i)
	{
		std::cout << ' ';
	}

	DrawScore();
	DrawPause();
}

void ScoreOverlay::Destroy()
{
}

ScoreOverlay::ScoreOverlay()
	: lastConsumeTime(std::chrono::steady_clock::now()),
	isPaused(false),
	score(0)
{
}
