#pragma once

class GlobalGameState
{
private:
	GlobalGameState() = default;

	bool levelReloadRequested;

	bool playerIsAlive;
	unsigned playerScore;

	int currentLevel;

public:
	void RequestLevelReload();
	void LevelLoaded();
	void AdvanceToNextLevel();
	
	void KillPlayer();
	void AddPlayerScore(unsigned score);
	void Reset();

	bool IsLevelReloadRequested() const;
	bool IsPlayerAlive() const;
	unsigned GetPlayerScore() const;

	int GetCurrentLevel() const;

	static GlobalGameState& Get();
};