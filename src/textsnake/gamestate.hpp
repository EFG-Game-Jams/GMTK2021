#pragma once

class GameState
{
public:
	virtual void Update(unsigned const elapsedMs) = 0;
	virtual void Awake() = 0;

	virtual ~GameState() = default;
};

