#include "levelstate.hpp"

void LevelState::Update(unsigned const elapsedMs)
{
}

void LevelState::Destroy()
{
}

void LevelState::Focus()
{
	// TODO load level(s) + player
}

LevelState::LevelState(int _level)
	: level(_level),
	loaded(false)
{
}
