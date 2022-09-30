#include "Tree.h"
#include "InputManager.h"
//log 텍스쳐 출력이 안됨
Tree::Tree(Texture& texTree, int num)
	:SpriteGameObject(texTree), texTree(texTree), treeNum(num),pos(Sides::Right)
{
	
	for (int i = 0; i < 100; ++i)
	{
		auto log = new EffectLog(RMI->GetTexture("graphics/2Plog.png"), 5.f);
		unuseLogs.push_back(log);
	}
}

Tree::~Tree()
{
}

void Tree::Init()
{
	sprite.setTexture(texTree);
	SetOrigin(Origins::BC);
	if (treeNum == 1)
	{
		SetPosition(Vector2f({ 500, 900 }));
	}
	else
	{
		SetPosition(Vector2f({ 1400, 900 }));
	}
	
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
	if (treeNum == 1)
	{
		if (InputManager::GetKeyDown(Keyboard::A))
		{
			ShowLogEffect();
		}
		if (InputManager::GetKeyDown(Keyboard::D))
		{
			ShowLogEffect();
		}
	}
	else
	{
		if (InputManager::GetKeyDown(Keyboard::Left))
		{
			ShowLogEffect();
		}
		if (InputManager::GetKeyDown(Keyboard::Right))
		{
			ShowLogEffect();
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

void Tree::ShowLogEffect()
{
	if (unuseLogs.empty())
		return;

	auto log = unuseLogs.front();
	unuseLogs.pop_front();
	useLogs.push_back(log);

	Vector2f force;
	force.x = pos == Sides::Left ? 1500 : -1500;
	force.y = -1500;
	float aForce = pos == Sides::Left ? 360 * 2 : -360 * 2;


	Vector2f pos({ 900,500 });
	//	= centerPos;
	//pos.y = axe.getPosition().y;//y축 도끼높이
	log->SetPosition(pos);
	log->SetOrigin(Origins::MC);
	log->Fire(force, aForce);
}

