#pragma once
#include <SFML/Audio.hpp>
#include "SpriteGameObject.h"
#include "Branch.h"
#include "EffectLog.h"
#include "ResourceManager.h"
#include <vector>
#include <list>

using namespace std;

class Player : public SpriteGameObject
{
private:
	std::list<EffectLog*> unuseLogs;
	std::list<EffectLog*> useLogs;

	Texture& texPlayer;

	Sprite spriteAxe;
	Sound chopSound;
	Sound deathSound;

	Sides pos;
	Vector2f centerPos;
	Vector2f axePos;
	bool isAlive;
	bool isChop;
	int score;

	std::vector<Vector2f> originalPos;

public:
	Player(Texture& player);

	void Set(Vector2f center);
	void Clear();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetFlipX(bool flip) override;

	void SetPosition(Vector2f pos);
	void ShowLogEffect();

	bool GetAlive() const;
	Sides GetPos() const;

	void IncreaseScore();
	int GetScore() const;

	void Chop(Sides side);
	void Die();
};

