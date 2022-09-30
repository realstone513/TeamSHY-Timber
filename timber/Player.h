#pragma once
#include "SpriteGameObject.h"
#include "ResourceManager.h"

using namespace std;

class Player : public SpriteGameObject
{
private:
	Texture& texPlayer;
	int GameMode;
	int is1P2P;
	Sides side;

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

	void Chop(Sides side);

	bool GetisChop();
};
