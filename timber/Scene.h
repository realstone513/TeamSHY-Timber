#pragma once
#include <string>

class Scene
{
private:
	std::string name;

public:
	Scene();
	~Scene();

	void Init();
	void Update();
	void Draw();
	void Release();
};

