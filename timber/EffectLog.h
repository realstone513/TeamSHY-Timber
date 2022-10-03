#pragma once
#include "SpriteGameObject.h"
class EffectLog : public SpriteGameObject
{
protected:
	Sides side;
	Vector2f velocity;
	float angularvelocity;
	float duration;
	float timer;
	bool active;

public:
	static const Vector2f Gravity;

	EffectLog(Texture& tex, float duration, Sides side);
	virtual ~EffectLog();

	void Fire(const Vector2f v, float av);
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	bool GetActive();
	Sides GetSide();
};

