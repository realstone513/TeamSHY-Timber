#pragma once
#include "SpriteGameObject.h"
#include "ResourceManager.h"
#include "EffectLog.h"
#include <list>


using namespace std;

enum class Sides
{
	Left,
	Right,
	None,
};

class Tree : public SpriteGameObject
{
private:
	Texture& texTree;
	Texture texLog;
	Sides pos;
	int treeNum;
	std::list<EffectLog*> unuseLogs;
	std::list<EffectLog*> useLogs;
public:
	Tree(Texture& texTree, int num);
	~Tree();

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	void ShowLogEffect();
	
};


