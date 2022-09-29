#pragma once
#include "SpriteGameObject.h"
#include "ResourceManager.h"

using namespace std;

class Player : public SpriteGameObject
{
private:
	Texture& texPlayer;
	int playerNum;
public:
	Player(Texture& player,int num);
	~Player();

	virtual void Init();
	virtual void Release();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void SetFlipX(bool flip);
};
