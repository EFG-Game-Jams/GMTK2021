#pragma once
#include "MessageOverlay.hpp"

class GameOverOverlay : public MessageOverlay
{
public:
	void Update(unsigned const elapsedMs) override;

	GameOverOverlay();
};
