#pragma once
#include "SpriteGameObject.h"
#include "ResourceManager.h"

class Tree;
using namespace std;

class Player : public SpriteGameObject
{
private:
	Texture& texPlayer;
	int GameMode;
	int is1P2P;
	Sides side;
	Sides currentbranchside;

	bool isAlive;
	bool isChop;

	Vector2f treePos;
	vector<Vector2f> originalPos;
public:
	Player(Texture& player,int gamemode,int is1P2P,Vector2f treepos);
	~Player();

	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void SetFlipX(bool flip);

	Sides CurrentBranchSide(Tree* side);
	void Chop(Sides side);
	void Die();

	bool GetisChop();
};
