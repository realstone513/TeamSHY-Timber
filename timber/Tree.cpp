#include "Tree.h"
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
					auto log = new EffectLog(PRMI->GetTexture("graphics/1P_log(b)_L.png"), 5.f,(Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 1:
				{
					auto log = new EffectLog(PRMI->GetTexture("graphics/1P_log(b)_R.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 2:
				{
					auto log = new EffectLog(PRMI->GetTexture("graphics/1P_log(b)_N.png"), 5.f, (Sides)i);
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
					auto log = new EffectLog(PRMI->GetTexture("graphics/2P_log(b)_L.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 1:
				{
					auto log = new EffectLog(PRMI->GetTexture("graphics/2P_log(b)_R.png"), 5.f, (Sides)i);
					unuseLogs[i].push_back(log);
					break;
				}
				case 2:
				{
					auto log = new EffectLog(PRMI->GetTexture("graphics/2P_log(b)_N.png"), 5.f, (Sides)i);
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
		if (this->GameMode == 1)
		{
			if (i == 0)
			{
				branches[i] = new Branch(PRMI->GetTexture("graphics/1P_log(b)_N.png"));
				branches[i]->SetSide(Sides::None, GameMode);
			}
			else
			{
				switch ((Sides)Utils::Range(0, 2))
				{
				case Sides::Left:
					branches[i] = new Branch(PRMI->GetTexture("graphics/1P_log(b)_L.png"));
					branches[i]->SetSide(Sides::Left,GameMode);
					break;
				case Sides::Right:
					branches[i] = new Branch(PRMI->GetTexture("graphics/1P_log(b)_R.png"));
					branches[i]->SetSide(Sides::Right, GameMode);
					break;
				case Sides::None:
					branches[i] = new Branch(PRMI->GetTexture("graphics/1P_log(b)_N.png"));
					branches[i]->SetSide(Sides::None, GameMode);
					break;
				}
			}
		}
		else
		{
			if (i == 0)
			{
				branches[i] = new Branch(PRMI->GetTexture("graphics/2P_log(b)_N.png"));
				branches[i]->SetSide(Sides::None, GameMode);
			}
			else
			{
				switch ((Sides)Utils::Range(0, 2))
				{
				case Sides::Left:
					branches[i] = new Branch(PRMI->GetTexture("graphics/2P_log(b)_L.png"));
					branches[i]->SetSide(Sides::Left, GameMode);
					break;
				case Sides::Right:
					branches[i] = new Branch(PRMI->GetTexture("graphics/2P_log(b)_R.png"));
					branches[i]->SetSide(Sides::Right, GameMode);
					break;
				case Sides::None:
					branches[i] = new Branch(PRMI->GetTexture("graphics/2P_log(b)_N.png"));
					branches[i]->SetSide(Sides::None, GameMode);
					break;
				}
			}
		}
		branches[i]->SetOrigin(Origins::BC);
	}
	if (this->GameMode == 1)
	{
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
	else
	{
		if (is1P2P == 1)
		{
			branchPosArr.resize(branches.size());
			float x = 480;
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
		else
		{
			branchPosArr.resize(branches.size());
			float x = 1440;
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
				ShowLogEffect(branches[currentBranche]->GetSide(), Sides::Left);
			}
			if (InputManager::GetKeyDown(Keyboard::D))
			{
				ShowLogEffect(branches[currentBranche]->GetSide(), Sides::Right);
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
					ShowLogEffect(branches[currentBranche]->GetSide(), Sides::Left);
				}
				if (InputManager::GetKeyDown(Keyboard::D))
				{
					ShowLogEffect(branches[currentBranche]->GetSide(), Sides::Right);
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
			if (!isChop)
			{
				if (InputManager::GetKeyDown(Keyboard::Left))
				{
					ShowLogEffect(branches[currentBranche]->GetSide(), Sides::Left);
				}
				if (InputManager::GetKeyDown(Keyboard::Right))
				{
					ShowLogEffect(branches[currentBranche]->GetSide(), Sides::Right);
				}
			}
			else
			{
				if (InputManager::GetKeyUp(Keyboard::Left))
				{
					isChop = false;
				}
				if (InputManager::GetKeyUp(Keyboard::Right))
				{
					isChop = false;
				}
			}
		}
	}
}

void Tree::Draw(RenderWindow& window)
{
	for (auto branch : branches)
	{
		branch->Draw(window);
	}
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


void Tree::ShowLogEffect(Sides branchside,Sides playerside)
{
	isChop = true;
	this->side = branchside;
	if (unuseLogs[(int)side].empty())
		return;

	auto log = unuseLogs[(int)side].front();
	unuseLogs[(int)side].pop_front();
	useLogs.push_back(log);

	Vector2f force;
	int forceRanX = 300; //Utils::Range(300, 800);
	force.x = playerside == Sides::Left ? forceRanX : -forceRanX;
	force.y = -800;
	float aForceRan = 360; // Utils::Range(360, 1800);
	float aForce = playerside == Sides::Left ? aForceRan : -aForceRan;

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
			branches[index]->SetSide((Sides)Utils::Range(0, 2), GameMode);
		}
	}
}

Sides Tree::GetCurrentBranchSide()
{
	return branches[currentBranche]->GetSide();
}
