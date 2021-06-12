#include "state.hpp"
#include "playingfield.hpp"

class TestState : public State
{
private:
	bool spawnedSnakes;
	PlayingField field;

public:
	virtual void Update(unsigned const elapsedMs) override;
	virtual void Focus() override;
	virtual void Destroy() override;

	TestState();
};
