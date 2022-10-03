//#pragma once
//#include <SFML/Graphics.hpp>
//#include <string>
//#include <list>
//#include "InputManager.h"
//#include "SpriteGameObject.h"
//
//using namespace sf;
//using namespace std;
//
//class Scene
//{
//private:
//	Scene(const Scene& ref);
//	Scene& operator= (const Scene& ref);
//
//protected:
//	list<SpriteGameObject*> gameObjectList;
//	Clock clock;
//	string name;
//	Time dt;
//
//public:
//	Scene(string _name);
//	virtual ~Scene();
//
//	virtual void Init();
//	virtual void Update();
//	virtual void Draw();
//	virtual void Release();
//};
//
//class Title : public Scene
//{
//private:
//
//public:
//	Title(string _name);
//	virtual ~Title() override;
//
//	virtual void Init() override;
//	virtual void Update() override;
//	virtual void Draw() override;
//	virtual void Release() override;
//};