#pragma once
#include "SpriteGameObject.h"
#include "SFML/Graphics.hpp"

using namespace sf;


class FloatingObject : public SpriteGameObject
{
private:
	float speed;
	Vector2i speedRange;
	Vector2i yRange;

	Vector2f direction;

	Vector2f startPos;
	Vector2f endPos;


public:
	FloatingObject(Texture& tex, Vector2f pos = Vector2f());
	virtual ~FloatingObject();

	virtual void Init() override;
	virtual void Update(float dt) override;

	void Set(Vector2i sRange, Vector2i yRange, Vector2f start, Vector2f end);

};