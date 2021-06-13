#pragma once

class State
{
public:
	virtual bool IsOverlay() const;
	virtual bool UpdateBelow() const;

	virtual void Update(unsigned const elapsedMs) = 0;
	// Clears the screen by default
	virtual void Focus();
	virtual void Destroy() = 0;

	virtual ~State() = default;
};

