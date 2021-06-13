#include "menufield.hpp"
#include "statestack.hpp"
#include "teststate.hpp"
#include "menustate.hpp"
#include "infostate.hpp"
#include "levelstate.hpp"
#include "soundeffect.hpp"
#include <cassert>

void MenuField::UpdateCollisions()
{
	for (std::size_t i = 1; i < snakes.size(); ++i)
	{
		if (Collides(*(snakes[0]), *(snakes[i])) != CollisionType::None)
		{
			auto& stateStack = StateStack::GetInstance();

			auto const snakeType = (snakes[i])->GetType();
			switch (snakeType)
			{
			case SnakeType::MenuGotoPlay:
				stateStack.PushState(std::make_unique<LevelState>(0));
				break;

			case SnakeType::MenuGotoTest:
				stateStack.PushState(std::make_unique<TestState>());
				break;

			case SnakeType::MenuGotoInfo:
				stateStack.PushState(std::make_unique<InfoState>());
				break;

			case SnakeType::MenuGotoMenu:
				stateStack.PushState(std::make_unique<MenuState>());
				break;

			default:
				assert(false);
				break;
			}

			PlaySoundEffect(SoundEffect::NEUTRAL1);
			for (auto const& snake : snakes)
				snake->ForceFreeze();
		}
	}
}
