#include "menufield.hpp"
#include "statestack.hpp"
#include "menustate.hpp"
#include "infostate.hpp"
#include "levelstate.hpp"
#include "soundeffect.hpp"
#include <cassert>
#include "gamewinoverlay.hpp"
#include "globalgamestate.hpp"

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
				GlobalGameState::Get().Reset();
				stateStack.PushState(std::make_unique<LevelState>(0));
				break;

			case SnakeType::MenuGotoTest:
				stateStack.PushState(std::make_unique<GameWinOverlay>());
				break;

			case SnakeType::MenuGotoInfo:
				stateStack.PushState(std::make_unique<InfoState>());
				break;

			case SnakeType::MenuGotoMenu:
				stateStack.PushState(std::make_unique<MenuState>());
				break;

			case SnakeType::MenuRequestReload:
				GlobalGameState::Get().RequestLevelReload();
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
