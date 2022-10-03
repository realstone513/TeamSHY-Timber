//#include "Scene.h"
//#include "ResourceManager.h"
//
//Scene::Scene(string _name)
//	: name(_name)
//{
//}
//
//Scene::Scene(const Scene& ref)
//{
//}
//
//Scene& Scene::operator=(const Scene& ref)
//{
//    return *this;
//}
//
//Scene::~Scene()
//{
//}
//
//void Scene::Init()
//{
//}
//
//void Scene::Update()
//{
//}
//
//void Scene::Draw()
//{
//}
//
//void Scene::Release()
//{
//    for (auto go : gameObjectList)
//    {
//        go->Release();
//        delete go;
//    }
//    gameObjectList.clear();
//}
//
//
//// Title
//Title::Title(string _name)
//    : Scene(_name)
//{
//}
//
//Title::~Title()
//{
//}
//
//void Title::Init()
//{
//    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
//}
//
//void Title::Update()
//{
//    Time dt = clock.restart();
//    Event ev;
//    InputManager::ClearInput();
//
//    while (window.pollEvent(ev))
//    {
//        InputManager::UpdateInput(ev);
//    }
//}
//
//void Title::Draw()
//{
//}
//
//void Title::Release()
//{
//}
