#include "menufield.hpp"
#include "statestack.hpp"
#include "teststate.hpp"
#include "menustate.hpp"
#include "infostate.hpp"

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
			case SnakeType::MenuGotoTest:
				stateStack.PushState(std::make_unique<TestState>(), true);
				return;

			case SnakeType::MenuGotoInfo:
				stateStack.PushState(std::make_unique<InfoState>(), true);
				return;

			case SnakeType::MenuGotoMenu:
				stateStack.PushState(std::make_unique<MenuState>(), true);
				return;

			default:
				break;
			}
		}
	}
}
