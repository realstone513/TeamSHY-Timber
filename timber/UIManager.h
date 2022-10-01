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
<<<<<<< HEAD
	map<string, Text*>		textMap;
	map<string, Shape*>		shapeMap;
	Font&					font;

public:
	UIManager(Font& _font);
	~UIManager();

	void Init();
	void Release();

	void SetTextUI(
		string textString,
		string name = "",
		int charSize = 75,
		Color textColor = Color::White);
	Text* GetTextUI(string name) const;
=======
	map<string, Text*> textMap;
	map<string, Shape*> shapeMap;

public:
	UIManager();
	~UIManager();

>>>>>>> d148df034bed63e75925ac500a78b7377e25d359
};