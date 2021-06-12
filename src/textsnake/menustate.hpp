#pragma once
#include "basestate.hpp"
#include "playingfield.hpp"

class MenuState : public State
{
private:
	PlayingField field;

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	MenuState();
	~MenuState();
};

