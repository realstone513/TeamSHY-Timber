#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "InputManager.h"
#include "UIManager.h"
#include "Player.h"
#include "Tree.h"


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

	bool playing;
	bool exit;

public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void Release();
	virtual void GetWindow(RenderWindow* _window);
	virtual void GetUIManager(UIManager* _um);
	
	bool Loop();
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

class SelectGameMode : public Scene
{
private:
	int gameMode;

public:
	SelectGameMode();
	virtual ~SelectGameMode() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	int GetGameMode();
};

class SelectCharacter : public Scene
{
private:
	int gameMode;
	int	character1p;
	int	character2p;
	bool ready1p;
	bool ready2p;

public:
	SelectCharacter(int gameMode);
	virtual ~SelectCharacter() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
	int GetCharacter1p();
	int GetCharacter2p();
};

class GamePlay : public Scene
{
private:
	int gameMode;
	int	character1p;
	int	character2p;
	bool gameOver;
	bool pause;
	float duration;
	float timer;
	float bonusTime;
	Sound timeOutSound;
	Vector2f timerBarSize;

	Player* player1;
	Player* player2;
	Tree* tree1;
	Tree* tree2;

public:
	GamePlay(int _mode, int player1, int player2);
	virtual ~GamePlay() override;

	virtual void Init() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void Release() override;
};