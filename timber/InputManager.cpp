#include "InputManager.h"
#include <iostream>

vector<bool> InputManager::downList(Keyboard::Key::KeyCount);
vector<bool> InputManager::ingList(Keyboard::Key::KeyCount);
vector<bool> InputManager::upList(Keyboard::Key::KeyCount);

vector<Keyboard::Key> InputManager::downList2;
vector<Keyboard::Key> InputManager::ingList2;
vector<Keyboard::Key> InputManager::upList2;

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
			/*downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);*/
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
	/*return find(downList.begin(), downList.end(), key) !=
		downList.end();*/
}
bool InputManager::GetKey(Keyboard::Key key)
{
	return ingList[(int)key];
	/*return find(ingList.begin(), ingList.end(), key) !=
		ingList.end();*/
}
bool InputManager::GetKeyUp(Keyboard::Key key)
{
	return upList[(int)key];
	/*return find(upList.begin(), upList.end(), key) !=
		upList.end();*/
}

void InputManager::ClearInput2()
{
	downList2.clear();
	upList2.clear();
}

void InputManager::UpdateInput2()
{
	// press
	//if (!GetKey(ev.key.code))
	//downList[(int)ev.key.code] = true;
	//ingList[(int)ev.key.code] = true;
	///*downList.push_back(ev.key.code);
	//ingList.push_back(ev.key.code);*/
	//// release
	//ingList[(int)ev.key.code] = false;
	//upList[(int)ev.key.code] = true;
}

bool InputManager::GetKeyDown2(Keyboard::Key key)
{
	return true;
}

bool InputManager::GetKey2(Keyboard::Key key)
{

	return true;
}

bool InputManager::GetKeyUp2(Keyboard::Key key)
{

	return true;
}