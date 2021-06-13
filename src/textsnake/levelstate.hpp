#pragma once
#include "state.hpp"
#include "playingfield.hpp"
#include <chrono>

class LevelState : public State
{
private:
	int level;
	bool loaded;
	std::chrono::steady_clock::time_point lastConsumeTime;
	PlayingField field;

	void LoadLevel();

public:
	void Update(unsigned const elapsedMs) override;
	void Focus() override;
	void Destroy() override;

	LevelState(int level);
};

