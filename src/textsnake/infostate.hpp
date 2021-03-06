#pragma once
#include "state.hpp"
#include "menufield.hpp"

class InfoState : public State
{
private:
	bool spawnedSnakes;
	MenuField field;

public:
	virtual void Update(unsigned const elapsedMs) override;
	virtual void Focus() override;
	virtual void Destroy() override;

	InfoState();
};

