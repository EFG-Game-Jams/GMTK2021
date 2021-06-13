#pragma once
#include "state.hpp"
#include "playingfield.hpp"

class LevelState : public State
{
private:
	int level;
	bool loaded;
	PlayingField field;

	void LoadLevel();

public:
	void Update(unsigned const elapsedMs) override;
	void Focus() override;
	void Destroy() override;

	LevelState(int level);
};

