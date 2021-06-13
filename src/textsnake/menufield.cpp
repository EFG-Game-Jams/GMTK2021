#include "menufield.hpp"
#include "statestack.hpp"
#include "teststate.hpp"
#include "menustate.hpp"
#include "infostate.hpp"
#include "levelstate.hpp"
#include "soundeffect.hpp"

void MenuField::UpdateCollisions()
{
	for (std::size_t i = 1; i < snakes.size(); ++i)
	{
		if (Collides(*(snakes[0]), *(snakes[i])) != CollisionType::None)
		{
			auto& stateStack = StateStack::GetInstance();

			snakes[0]->ForceFreeze();

			auto const snakeType = (snakes[i])->GetType();
			switch (snakeType)
			{
			case SnakeType::MenuGotoPlay:
				stateStack.SchedulePushState(std::make_unique<LevelState>(0));
				PlaySoundEffect(SoundEffect::NEUTRAL1);
				return;

			case SnakeType::MenuGotoTest:
				stateStack.SchedulePushState(std::make_unique<TestState>());
				PlaySoundEffect(SoundEffect::NEUTRAL1);
				return;

			case SnakeType::MenuGotoInfo:
				stateStack.SchedulePushState(std::make_unique<InfoState>());
				PlaySoundEffect(SoundEffect::NEUTRAL1);
				return;

			case SnakeType::MenuGotoMenu:
				stateStack.SchedulePushState(std::make_unique<MenuState>());
				PlaySoundEffect(SoundEffect::NEUTRAL1);
				return;

			default:
				break;
			}
		}
	}
}
