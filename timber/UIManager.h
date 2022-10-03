#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include "Singleton.h"

using namespace sf;
using namespace std;

class UIManager
{
private:
	map<string, Text*>				textMap;
	map<string, RectangleShape*>	rectangleMap;
	Font&							font;
	Vector2u						wSize;

public:
	UIManager(Font& _font, Vector2u windowSize = { 0, 0 });
	~UIManager();

	void Init();
	void Release();

	void SetTextUI(
		string textString,
		string name = "",
		int charSize = 75,
		Color textColor = Color::White);
	Text* GetTextUI(string name) const;

	void SetRectangleUI(
		string name,
		Vector2f size,
		Color shapeColor = Color::White);

	void SetRectangleUI(
		string name,
		float sizeX, float sizeY,
		Color shapeColor = Color::White);

	RectangleShape* GetRectangleUI(string name) const;

	Vector2u GetwSize() const;
};