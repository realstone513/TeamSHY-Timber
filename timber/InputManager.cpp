#include "InputManager.h"
#include <iostream>

vector<bool> InputManager::downList(Keyboard::Key::KeyCount);
vector<bool> InputManager::ingList(Keyboard::Key::KeyCount);
vector<bool> InputManager::upList(Keyboard::Key::KeyCount);

void InputManager::ClearInput()
{
	fill(downList.begin(), downList.end(), false);
	fill(upList.begin(), upList.end(), false);
}

void InputManager::UpdateInput(Event& ev)
{
	switch (ev.type)
	{
	case Event::EventType::KeyPressed:
		if (ev.key.code != Keyboard::Key::Unknown &&
			!ingList[ev.key.code])
		{
			downList[(int)ev.key.code] = true;
			ingList[(int)ev.key.code] = true;
		}
		break;
	case Event::EventType::KeyReleased:
		if (ev.key.code != Keyboard::Key::Unknown)
		{
			ingList[(int)ev.key.code] = false;
			upList[(int)ev.key.code] = true;
		}
		break;
	}
}

bool InputManager::GetKeyDown(Keyboard::Key key)
{
	return downList[(int)key];
}

bool InputManager::GetKey(Keyboard::Key key)
{
	return ingList[(int)key];
}

bool InputManager::GetKeyUp(Keyboard::Key key)
{
	return upList[(int)key];
}