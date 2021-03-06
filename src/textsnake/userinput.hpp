#pragma once
#include <unordered_set>

enum class PlayerActions
{
	Escape,
	MoveUp,
	MoveDown,
	MoveLeft,
	MoveRight,
	Pause,
	Action
};

class UserInput
{
private:
	std::unordered_set<PlayerActions> playerActionPresses;
	std::unordered_set<PlayerActions> playerActionReleases;

	friend class Game;
	void ClearState();
	void Update();

	UserInput() = default;
	~UserInput() = default;

public:
	bool WasThereAnyAction() const;
	bool WasActionPressed(PlayerActions const action) const;
	bool WasActionReleased(PlayerActions const action) const;

	static UserInput & GetInstance();
};

