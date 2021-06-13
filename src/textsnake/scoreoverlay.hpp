#pragma once
#include "state.hpp"
#include <chrono>

class ScoreOverlay : public State
{
private:
	std::chrono::steady_clock::time_point lastConsumeTime;
	bool isPaused;
	unsigned score;

	void DrawScore() const;
	void DrawPause() const;

public:
	bool IsOverlay() const override;
	bool UpdateBelow() const override;
	void Update(unsigned const elapsedMs) override;
	void Focus() override;
	void Destroy() override;

	ScoreOverlay();
};

