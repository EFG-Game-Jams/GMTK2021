#pragma once

class State
{
public:
	virtual bool IsOverlay() const;

	virtual void Update(unsigned const elapsedMs) = 0;
	virtual void Focus() = 0;
	virtual void Destroy() = 0;

	virtual ~State() = default;
};

