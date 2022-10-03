#pragma once
#include <SFML/Graphics.hpp>
#include "UIManager.h"
#include <string>
#include <list>
#include "InputManager.h"
#include "SpriteGameObject.h"

using namespace sf;
using namespace std;

class GameManager
{
public:
	class Scene
	{
	private:
		Scene(const Scene& ref);
		Scene& operator= (const Scene& ref);

	protected:
		list<SpriteGameObject*> gameObjectList;
		Clock clock;
		Time dt;
	public:
		Scene();
		virtual ~Scene();

		virtual void Init();
		virtual void Update();
		virtual void Draw();
		virtual void Release();
		
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

	GameManager();
	~GameManager();

	void			PlayScene(Scene* _scene);
	RenderWindow*	GetWindow();
	Scene*			GetScene();

protected:
	static RenderWindow*	window;
	static UIManager*		um;

private:
	Scene*			currentScene;
	Vector2u		wSize;
};