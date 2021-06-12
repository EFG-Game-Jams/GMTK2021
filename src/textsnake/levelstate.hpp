#pragma once
#include "state.hpp"

class LevelState : public State
{
private:
	int level;
	bool loaded;

public:
	virtual void Update(unsigned const elapsedMs) override;
	virtual void Focus() override;
	virtual void Destroy() override;

	LevelState(int level);
};

