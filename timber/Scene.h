#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "InputManager.h"
#include "SpriteGameObject.h"
#include "UIManager.h"

using namespace sf;
using namespace std;

class Scene
{
private:
	Scene(const Scene& ref);
	Scene& operator= (const Scene& ref);

protected:
	list<SpriteGameObject*> gameObjectList;
	RenderWindow*			window;
	UIManager*				um;
	Clock					clock;
	Time					dt;

public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();
	virtual void GetWindow(RenderWindow* _window);
	virtual void GetUIManager(UIManager* _um);
	
	bool playing;
};

class Title : public Scene
{
public:
	Title();
	virtual ~Title() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};

class Menu : public Scene
{
private:
	int		gameMode;

public:
	Menu(int& _gameMode);
	virtual ~Menu() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};