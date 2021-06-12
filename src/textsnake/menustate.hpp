#pragma once
#include "gamestate.hpp"
#include "menufield.hpp"

class MenuState : public GameState
{
private:
	bool spawnedSnakes;
	MenuField field;

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	MenuState();
	~MenuState();
};

