#pragma once
#include "state.hpp"
#include <chrono>

class ScoreOverlay : public State
{
private:
	bool isPaused;
	unsigned score;
	unsigned level;

	void DrawScore() const;
	void DrawPause() const;
	void DrawCurrentLevel() const;

public:
	bool IsOverlay() const override;
	bool UpdateBelow() const override;
	void Update(unsigned const elapsedMs) override;
	void Focus() override;
	void Destroy() override;

	unsigned GetScore() const;

	ScoreOverlay();
};

