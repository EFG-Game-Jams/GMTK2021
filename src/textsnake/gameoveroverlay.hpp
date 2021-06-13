#pragma once
#include "MessageOverlay.hpp"
#include "menufield.hpp"
#include <chrono>

class GameOverOverlay : public MessageOverlay
{
private:
	std::chrono::steady_clock::time_point lastConsumeTime;
	unsigned elapsedTotal;
	bool menuLoaded;
	MenuField field;

	void LoadMenu();

public:
	void Update(unsigned const elapsedMs) override;

	GameOverOverlay();
};
