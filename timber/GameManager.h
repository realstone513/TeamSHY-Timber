#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "UIManager.h"
#include "InputManager.h"
#include "SpriteGameObject.h"
#include "Scene.h"

using namespace sf;
using namespace std;

class GameManager
{
public:
	RenderWindow*	window;
	UIManager*		um;
	int				gameMode;
	int				character1p;
	int				character2p;
	bool			selectGameMode;
	bool			selectCharacter;

	GameManager();
	~GameManager();

	void			PlayScene(Scene* _scene);
	void			ReleaseScene();
	RenderWindow*	GetWindow();
	Scene*			GetScene();

private:
	Scene*			currentScene;
	Vector2u		wSize;
};