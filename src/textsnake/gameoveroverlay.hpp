#pragma once
#include "MessageOverlay.hpp"
#include "menufield.hpp"
#include <chrono>

class GameOverOverlay : public MessageOverlay
{
private:
	unsigned elapsedTotal;
	bool menuLoaded;
	MenuField field;

	void LoadMenu();

public:
	void Update(unsigned const elapsedMs) override;

	GameOverOverlay();
};
