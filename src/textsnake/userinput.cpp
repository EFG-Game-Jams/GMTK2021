#include "event.hpp"
#include "userinput.hpp"

void UserInput::ClearState()
{
	playerActionPresses.clear();
	playerActionReleases.clear();
}

void UserInput::Update()
{
	unsigned const bufferSize = 64;
	std::vector<Event::InputEvent> buffer;
	buffer.resize(bufferSize);

	Event::GetAll(buffer); // TODO check if we ever get more than 64 events per call

	ClearState();

	for (auto const & ev : buffer)
	{
		switch (ev.GetEventType())
		{
		case Event::Type::KEY:
			// https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes
			switch (ev.Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_ESCAPE:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::Escape);
				else
					playerActionReleases.insert(PlayerActions::Escape);
				break;
			case VK_UP:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveUp);
				else
					playerActionReleases.insert(PlayerActions::MoveUp);
				break;
			case VK_DOWN:
				if(ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveDown);
				else
					playerActionReleases.insert(PlayerActions::MoveDown);
				break;
			case VK_LEFT:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveLeft);
				else
					playerActionReleases.insert(PlayerActions::MoveLeft);
				break;
			case VK_RIGHT:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::MoveRight);
				else
					playerActionReleases.insert(PlayerActions::MoveRight);
				break;
			case VK_DELETE:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::Pause);
				else
					playerActionReleases.insert(PlayerActions::Pause);
				break;
			case VK_SPACE:
			case VK_RETURN:
				if (ev.Event.KeyEvent.bKeyDown)
					playerActionPresses.insert(PlayerActions::Action);
				else
					playerActionReleases.insert(PlayerActions::Action);
				break;
			}
			break;
		default:
			break;
		}
	}
}

bool UserInput::WasThereAnyAction() const
{
	return !(playerActionPresses.empty() && playerActionReleases.empty());
}

bool UserInput::WasActionPressed(PlayerActions const action) const
{
	if (playerActionPresses.find(action) == playerActionPresses.end())
	{
		return false;
	}

	return true;
}

bool UserInput::WasActionReleased(PlayerActions const action) const
{
	if (playerActionReleases.find(action) == playerActionReleases.end())
	{
		return false;
	}

	return true;
}

UserInput & UserInput::GetInstance()
{
	static UserInput evHandler;
	return evHandler;
}
