#include "Tree.h"
#include "Player.h"
#include "InputManager.h"
#include "EffectLog.h"

Tree::Tree(Texture& texTree,int gamemode, int is1P2P)
	:SpriteGameObject(texTree), texTree(texTree), side(Sides::Right), GameMode(gamemode), is1P2P(is1P2P), isChop(false), currentBranche(-1)
{
	unuseLogs.resize(3);

	if (this->GameMode == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 30; ++j)
			{
				switch (i)
				{
				case 0:
				{
					auto log = new EffectLog(RMI->GetTexture("graphics/1P_log(b)_L.png"), 5.f,(Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 1:
				{
					auto log = new EffectLog(RMI->GetTexture("graphics/1P_log(b)_R.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 2:
				{
					auto log = new EffectLog(RMI->GetTexture("graphics/1P_log(b)_N.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j <50; ++j)
			{
				switch (i)
				{
				case 0:
				{
					auto log = new EffectLog(RMI->GetTexture("graphics/2P_log(b)_L.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 1:
				{
					auto log = new EffectLog(RMI->GetTexture("graphics/2P_log(b)_R.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 2:
				{
					auto log = new EffectLog(RMI->GetTexture("graphics/2P_log(b)_N.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				}
			}
		}
	}

	branches.resize(6);
	for (int i = 0; i < branches.size(); i++)
	{
		if (i == 0)
		{
			branches[i] = new Branch(RMI->GetTexture("graphics/1P_log(b)_N.png"));
			branches[i]->SetSide(Sides::None);
		}
		else
		{
			switch ((Sides)Utils::Range(0, 2))
			{
			case Sides::Left:
				branches[i]= new Branch(RMI->GetTexture("graphics/1P_log(b)_L.png"));
				branches[i]->SetSide(Sides::Left);
				break;
			case Sides::Right:
				branches[i] = new Branch(RMI->GetTexture("graphics/1P_log(b)_R.png"));
				branches[i]->SetSide(Sides::Right);
				break;
			case Sides::None:
				branches[i] = new Branch(RMI->GetTexture("graphics/1P_log(b)_N.png"));
				branches[i]->SetSide(Sides::None);
				break;
			}
		}
		branches[i]->SetOrigin(Origins::BC);
	}

	branchPosArr.resize(branches.size());
	float x = 960;
	float y = 750;
	float offset = branches[0]->GetSize().y;
	//	offset +=30;
	for (int i = 0; i < branches.size(); ++i)
	{
		branchPosArr[i] = Vector2f(x, y);
		y -= offset;
	}

	UpdateBranches();
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
	
	for (auto it=unuseLogs.begin();it<unuseLogs.end();it++)
	{
		for (auto log : *it)
		{
			delete log;
		}
		it->clear();
	}
	unuseLogs.clear();

	for (auto log : useLogs)
	{
		delete log;
	}
	useLogs.clear();
}

// 동시 입력시 입력이 안되는 현상 수정 필요
void Tree::Update(float dt)
{
	SpriteGameObject::Update(dt);

	auto it = useLogs.begin();
	while (it != useLogs.end())
	{
		(*it)->Update(dt);
		if (!(*it)->GetActive())
		{
			unuseLogs[(int)(*it)->GetSide()].push_back(*it);
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
				ShowLogEffect(branches[currentBranche]->GetSide());
			}
			if (InputManager::GetKeyDown(Keyboard::D))
			{
				ShowLogEffect(branches[currentBranche]->GetSide());
			}
		}
		else
		{
			if (InputManager::GetKeyUp(Keyboard::A))
			{
				isChop = false;
			}
			if (InputManager::GetKeyUp(Keyboard::D))
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
	for (auto branch : branches)
	{
		branch->Draw(window);

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
	if (unuseLogs[(int)side].empty())
		return;

	auto log = unuseLogs[(int)side].front();
	unuseLogs[(int)side].pop_front();
	useLogs.push_back(log);

	Vector2f force;
	int forceRanX = 300; //Utils::Range(300, 800);
	force.x = side == Sides::Left ? forceRanX : -forceRanX;
	force.y = -800;
	float aForceRan = 360; // Utils::Range(360, 1800);
	float aForce = side == Sides::Left ? aForceRan : -aForceRan;

	Vector2f pos;
	
	pos.x = GetPosition().x;
	pos.y = 840;
	//pos.y = axe.getPosition().y;//y축 도끼높이
	log->SetPosition(pos);
	log->SetOrigin(Origins::MC);
	log->Fire(force, aForce);
	UpdateBranches();
}

void Tree::UpdateBranches()
{
	currentBranche = (currentBranche + 1) % branches.size();

	for (int i = 0; i < branches.size(); ++i)
	{
		int index = (currentBranche + i) % branches.size();
		branches[index]->SetPosition(branchPosArr[i]);
		if (i == branches.size() - 1)
		{
			branches[index]->SetSide((Sides)Utils::Range(0, 2));
		}
	}
}