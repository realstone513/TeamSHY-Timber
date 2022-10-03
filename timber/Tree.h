#pragma once
#include "SpriteGameObject.h"
#include "ResourceManager.h"
#include "EffectLog.h"
#include "Branch.h"
#include <list>
#include <vector>

using namespace std;

class Tree : public SpriteGameObject
{
private:
	Texture& texTree;
	Texture texLog;
	Sides side;
	int GameMode;
	int is1P2P;
	bool isChop;

	vector<list<EffectLog*>> unuseLogs;
	list<EffectLog*> useLogs;

	vector<Branch*> branches;
	vector<Vector2f> branchPosArr;
	int currentBranche;
	

public:
	

	Tree(Texture& texTree,int gamemode, int is1P2P);
	~Tree();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
	virtual void SetFlipX(bool flip);

	void ShowLogEffect(Sides branchside, Sides playerside);
	void UpdateBranches();
	Sides GetCurrentBranchSide();
};