#pragma once
#include "SpriteGameObject.h"
#include "ResourceManager.h"

class Tree;
using namespace std;

class Player : public SpriteGameObject
{
private:
	Texture& texPlayer;
	Sprite texAxe;
	Sound chopSound;
	Sound deathSound;

	int gameMode;
	int is1P2P;
	Sides side;
	Sides currentbranchside;

	bool isAlive;
	bool isChop;

	int score;
	int addScore;
	int minusScore;
	bool scoreStatus;

	Vector2f treePos;
	vector<Vector2f> originalPos;
	Vector2f axePos;

public:
	Player(Texture& player, int gamemode, int is1P2P, Vector2f treepos, Texture& axe, int characterType);
	~Player();

	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void SetPosition(Vector2f pos);
	virtual void SetFlipX(bool flip);

	void Chop(Sides side);
	void Die();

	bool GetisChop();
	Sides GetPlayerSide();

	int GetScore();
	void SetScoreStatus();
};