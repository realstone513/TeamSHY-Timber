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
	map<string, Text*> textMap;
	map<string, Shape*> shapeMap;

public:
	UIManager();
	~UIManager();

};