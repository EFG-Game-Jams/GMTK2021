#pragma once
#include "gamestate.hpp"
#include "menufield.hpp"

class InfoState : public GameState
{
private:
	bool spawnedSnakes;
	MenuField field;

public:
	virtual void Update(unsigned const elapsedMs) override;
	virtual void Awake() override;

	InfoState();
};

