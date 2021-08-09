#pragma once
#include "state.hpp"
#include "playingfield.hpp"
#include "messageoverlay.hpp"

class GameWinOverlay : public MessageOverlay
{
private:
	PlayingField field;

public:
	void Update(unsigned const elapsedMs) override;
	void Focus() override;
	void Destroy() override;

	GameWinOverlay();
};

