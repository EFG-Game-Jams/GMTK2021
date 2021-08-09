#include "scoreoverlay.hpp"
#include "statestack.hpp"
#include "gameoveroverlay.hpp"
#include "config.hpp"
#include "cursor.hpp"
#include <cstdio>
#include "soundeffect.hpp"
#include "globalgamestate.hpp"

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

void ScoreOverlay::DrawCurrentLevel() const
{
	std::cout << COORD{ 15, Config::consoleBufferSize.Y - 1 } << Config::scoreBoardColor;
	std::cout << "LEVEL: " << level;
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
	auto const& state = GlobalGameState::Get();
	if (!state.IsPlayerAlive() && !isPaused)
	{
		isPaused = true;
		StateStack::GetInstance().PushState(std::make_unique<GameOverOverlay>());
	}
	else if (level != state.GetCurrentLevel())
	{
		level = state.GetCurrentLevel();
		isPaused = true;
		PlaySoundEffect(SoundEffect::TWINKLEGOOD1);
		DrawCurrentLevel();
		DrawPause();
	}
	else if (score != state.GetPlayerScore())
	{
		score = state.GetPlayerScore();
		DrawScore();
	}
	else if (state.IsLevelReloadRequested())
	{
		isPaused = false;
		DrawPause();
	}

	auto& userInput = UserInput::GetInstance();
	if (state.IsPlayerAlive() && userInput.WasActionPressed(PlayerActions::Pause))
	{
		isPaused = !isPaused;
		DrawPause();
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
	DrawCurrentLevel();
}

void ScoreOverlay::Destroy()
{
}

unsigned ScoreOverlay::GetScore() const
{
	return score;
}

ScoreOverlay::ScoreOverlay()
	: isPaused(false),
	score(GlobalGameState::Get().GetPlayerScore()),
	level(GlobalGameState::Get().GetCurrentLevel())
{
}
