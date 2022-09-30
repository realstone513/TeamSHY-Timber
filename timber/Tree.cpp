#include "Tree.h"
#include "Player.h"
#include "InputManager.h"
//log 텍스쳐 출력이 안됨
Tree::Tree(Texture& texTree,int gamemode, int is1P2P)
	:SpriteGameObject(texTree), texTree(texTree), side(Sides::Right), GameMode(gamemode), is1P2P(is1P2P)
{
	for (int i = 0; i < 100; ++i)
	{
		if (GameMode == 1)
		{
			auto log = new EffectLog(RMI->GetTexture("graphics/log.png"), 5.f);
			unuseLogs.push_back(log);
		}
		else
		{
			if (GameMode == 1)
			{
				auto log = new EffectLog(RMI->GetTexture("graphics/2log.png"), 5.f);
				unuseLogs.push_back(log);
			}
			else
			{
				auto log = new EffectLog(RMI->GetTexture("graphics/2Plog.png"), 5.f);
				unuseLogs.push_back(log);
			}

		}
	}
}

Tree::~Tree()
{
}

void Tree::Init()
{
	sprite.setTexture(texTree,true);
	SetOrigin(Origins::BC);
	
}

void Tree::Release()
{
	for (auto log : unuseLogs)
	{
		delete log;
	}
	unuseLogs.clear();

	for (auto log : useLogs)
	{
		delete log;
	}
	useLogs.clear();
}

void Tree::Update(float dt)
{
	SpriteGameObject::Update(dt);

	auto it = useLogs.begin();
	while (it != useLogs.end())
	{
		(*it)->Update(dt);
		if (!(*it)->GetActive())
		{
			unuseLogs.push_back(*it);
			it = useLogs.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (GameMode == 1)
	{
		if (!isChop)
		{
			if (InputManager::GetKeyDown(Keyboard::A))
			{
				ShowLogEffect(Sides::Left);
			}
			if (InputManager::GetKeyDown(Keyboard::D))
			{
				ShowLogEffect(Sides::Right);
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
		if (is1P2P == 1)
		{
			if (!isChop)
			{
				if (InputManager::GetKeyDown(Keyboard::A))
				{
					ShowLogEffect(Sides::Left);
				}
				if (InputManager::GetKeyDown(Keyboard::D))
				{
					ShowLogEffect(Sides::Right);
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
					ShowLogEffect(Sides::Left);
				}
				if (InputManager::GetKeyDown(Keyboard::Right))
				{
					ShowLogEffect(Sides::Right);
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
	}
	
}

void Tree::Draw(RenderWindow& window)
{
	SpriteGameObject::Draw(window);
	for (auto log : useLogs)
	{
		log->Draw(window);
	}

}

void Tree::SetFlipX(bool flip)
{
	SpriteGameObject::SetFlipX(flip);
}


void Tree::ShowLogEffect(Sides side)
{
	isChop = true;
	this->side = side;
	if (unuseLogs.empty())
		return;

	auto log = unuseLogs.front();
	unuseLogs.pop_front();
	useLogs.push_back(log);

	Vector2f force;
	int forceRanX = Utils::Range(300, 800);
	force.x = side == Sides::Left ? forceRanX : -forceRanX;
	force.y = -800;
	float aForceRan = Utils::Range(360, 1800);
	float aForce = side == Sides::Left ? aForceRan : -aForceRan;


	Vector2f pos;
	
	pos.x = GetPosition().x;
	pos.y = 840;
	//pos.y = axe.getPosition().y;//y축 도끼높이
	log->SetPosition(pos);
	log->SetOrigin(Origins::MC);
	log->Fire(force, aForce);
}

