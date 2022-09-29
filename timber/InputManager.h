#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <conio.h>
#include <windows.h>

// static 함수를 이용해서
// 키보드 및 마우스 입력을 검사할 수 있는 클래스

using namespace sf;
using namespace std;

class InputManager
{
private:
	static vector<bool> downList;
	static vector<bool> ingList;
	static vector<bool> upList;

	static vector<Keyboard::Key> downList2;
	static vector<Keyboard::Key> ingList2;
	static vector<Keyboard::Key> upList2;

public:
	static void ClearInput();
	static void UpdateInput(Event& ev);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);

	// sfml 이벤트 안쓰고 만들기
	static void ClearInput2();
	static void UpdateInput2();

	static bool GetKeyDown2(Keyboard::Key key);
	static bool GetKey2(Keyboard::Key key);
	static bool GetKeyUp2(Keyboard::Key key);
};