#include "Player.h"
#include "InputManager.h"
#include "Tree.h"

Player::Player(Texture& player, int gamemode, int is1P2P, Vector2f treepos)
	:SpriteGameObject(player), texPlayer(player), GameMode(gamemode), is1P2P(is1P2P), isChop(false), treePos(treepos),originalPos(2)
{
}

Player::~Player()
{
}

void Player::Init()
{
	sprite.setTexture(texPlayer, true);
	SetOrigin(Origins::BC);
	if (is1P2P == 1)
	{
		SetPosition(Vector2f({ 300, 1000 }));
	}
	else
	{
		SetPosition(Vector2f({ 900, 1000 }));
	}
	isChop = false;	

	Vector2f size = GetSize();
	originalPos[(int)Sides::Left].x = treePos.x - size.x * 2;
	originalPos[(int)Sides::Left].y = treePos.y;

	originalPos[(int)Sides::Right].x = treePos.x + size.x * 2;
	originalPos[(int)Sides::Right].y = treePos.y;

	SetFlipX(side == Sides::Left);
	SetPosition(originalPos[(int)side]);
	
}

void Player::Release()
{
}

void Player::Update(float dt)
{
	SpriteGameObject::Update(dt);
	if (is1P2P == 1)
	{
		if (!isChop)
		{
			if (InputManager::GetKeyDown(Keyboard::A))
			{
				//SetPosition({ 300,1000 });
				Chop(Sides::Left);
			}
			if (InputManager::GetKeyDown(Keyboard::D))
			{
				//SetPosition({ 500,1000 });
				Chop(Sides::Right);
			}
		}
		else
		{
			if (side == Sides::Left && InputManager::GetKeyUp(Keyboard::A))
			{
				isChop = false;
			}
			if (side == Sides::Right && InputManager::GetKeyUp(Keyboard::D))
			{
				isChop = false;
			}
		}
	}
	else
	{
		if (!isChop)
		{
			if (InputManager::GetKeyDown(Keyboard::Left))
			{
				Chop(Sides::Left);
			}
			if (InputManager::GetKeyDown(Keyboard::Right))
			{
				Chop(Sides::Right);
			}
		}
		else
		{
			if (side == Sides::Left && InputManager::GetKeyUp(Keyboard::Left))
			{
				isChop = false;
			}
			if (side == Sides::Right && InputManager::GetKeyUp(Keyboard::Right))
			{
				isChop = false;
			}
		}
	}
	if (side == currentbranchside)
	{
		Die();
		isChop = false;
	}
}

void Player::Draw(RenderWindow& window)
{
	SpriteGameObject::Draw(window);
}

void Player::SetFlipX(bool flip)
{
	SpriteGameObject::SetFlipX(flip);
}

void Player::Chop(Sides side)
{
	isChop = true;
	this->side = side;
	SetFlipX(this->side == Sides::Left);
	SetPosition(originalPos[(int)side]);
	//IncreaseScore();
}

void Player::Die()
{
	//플레이어 죽음
	//1. 그림 바꾸기
	//2. 도끼 x
	//3. 키 입력 막아야 하고
	isAlive = false;
	isChop = false;
	sprite.setTexture(RMI->GetTexture("graphics/rip.png"), true);
	SetFlipX(false);
	Utils::SetOrigin(sprite, Origins::BC);
	//soundDeath.play();
}

Sides Player::CurrentBranchSide(Tree* side)
{
	return currentbranchside =side->CurrentBranchSide();
}
