#pragma once
#include "state.hpp"
#include "menufield.hpp"

class MenuState : public State
{
private:
	bool spawnedSnakes;
	MenuField field;

public:
	void Update(unsigned const elapsedMs) override;
	void Focus() override;
	void Destroy() override;

	MenuState();
};

