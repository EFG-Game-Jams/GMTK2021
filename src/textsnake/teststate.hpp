#include "gamestate.hpp"
#include "playingfield.hpp"

class TestState : public GameState
{
private:
	bool spawnedSnakes;
	PlayingField field;

public:
	virtual void Update(unsigned const elapsedMs) override;
	virtual void Awake() override;

	TestState();
};
