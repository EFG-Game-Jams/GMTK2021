#pragma once
#include "basestate.hpp"
#include "player.hpp"

class PlayingState : public State
{
private:
	Player player;

	void Pause();

	void HandleInput(UserInput const & evHandler);

public:
	void Update(unsigned const elapsedMs) override;
	void Awake() override;

	PlayingState();
	~PlayingState();
};

