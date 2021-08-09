#include "globalgamestate.hpp"

void GlobalGameState::RequestLevelReload()
{
	levelReloadRequested = true;
}

void GlobalGameState::LevelLoaded()
{
	levelReloadRequested = false;
	playerIsAlive = true;
}

void GlobalGameState::AdvanceToNextLevel()
{
	levelReloadRequested = false;
	playerIsAlive = true;
	++currentLevel;
}

void GlobalGameState::KillPlayer()
{
	playerIsAlive = false;
}

void GlobalGameState::AddPlayerScore(unsigned score)
{
	playerScore += score;
}

void GlobalGameState::Reset()
{
	currentLevel = 1;
	playerScore = 0;
}

bool GlobalGameState::IsLevelReloadRequested() const
{
	return levelReloadRequested;
}

bool GlobalGameState::IsPlayerAlive() const
{
	return playerIsAlive;
}

unsigned GlobalGameState::GetPlayerScore() const
{
	return playerScore;
}

int GlobalGameState::GetCurrentLevel() const
{
	return currentLevel;
}

GlobalGameState& GlobalGameState::Get()
{
	static GlobalGameState state{};

	return state;
}
