#include "Player.h"
#include "InputManager.h"

Player::Player(Texture& player, int num)
	:SpriteGameObject(player), texPlayer(player),playerNum(num)
{
}

Player::~Player()
{
}

void Player::Init()
{
	sprite.setTexture(texPlayer, true);
	SetOrigin(Origins::BC);
	if (playerNum == 1)
	{
		SetPosition(Vector2f({ 300, 1000 }));
	}
	else
	{
		SetPosition(Vector2f({ 900, 1000 }));
	}
		
	
}

void Player::Release()
{
}

void Player::Update(float dt)
{
	SpriteGameObject::Update(dt);
	if (playerNum == 1)
	{
		if (InputManager::GetKeyDown(Keyboard::A))
		{
			SetPosition({ 300,1000 });
		}
		if (InputManager::GetKeyDown(Keyboard::D))
		{
			SetPosition({ 500,1000 });
		}
	}
	else
	{
		if (InputManager::GetKeyDown(Keyboard::Left))
		{
			SetPosition({ 900,1000 });
		}
		if (InputManager::GetKeyDown(Keyboard::Right))
		{
			SetPosition({ 1100,1000 });
		}
	}
}

void Player::Draw(RenderWindow& window)
{
	SpriteGameObject::Draw(window);
}

void Player::SetFlipX(bool flip)
{
}
