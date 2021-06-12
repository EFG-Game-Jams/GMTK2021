#pragma once
#include "basestate.hpp"
#include "playingfield.hpp"

class MenuState : public State
{
private:
	PlayingField field;

	void Pause();

	void HandleInput(UserInput const & evHandler);

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	MenuState();
	~MenuState();
};

