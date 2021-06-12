#pragma once
#include "playingfield.hpp"

class MenuField : public PlayingField
{
protected:
	void UpdateCollisions() override;
};

