#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "UIManager.h"
#include "SpriteGameObject.h"

using namespace std;
using namespace sf;

class Scene;

class GameManager
{
private:
	RenderWindow*			window;
	UIManager*				um;

	list<SpriteGameObject*> gameObjectList;
	Vector2u				wSize;

	//Scene& currentScene;
public:
	GameManager();
	~GameManager();

	void Init();
	void Update();
	void Draw();
	void Clear();
	void Release();

	RenderWindow* GetWindow();
};