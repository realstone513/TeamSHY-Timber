#include "GameManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

GameManager::GameManager()
{
    VideoMode vm(1920, 1080);
    window = new RenderWindow(vm, "timber", Style::Default);
    wSize = window->getSize();
    um = new UIManager(RMI->GetFont("fonts/KOMIKAP_.ttf"));
    um->Init();
}

GameManager::~GameManager()
{
    um->Release();
    delete um;
    delete window;
}

void GameManager::PlayScene(Scene* _scene)
{
    currentScene = _scene;
}

RenderWindow* GameManager::GetWindow()
{
    return window;
}

GameManager::Scene* GameManager::GetScene()
{
    return currentScene;
}

// Scene
GameManager::Scene::Scene(const Scene& ref)
{
}
GameManager::Scene& GameManager::Scene::operator=(const Scene& ref)
{
    return *this;
}

GameManager::Scene::Scene()
    : playing(true)
{
}

GameManager::Scene::~Scene()
{
}

void GameManager::Scene::Init()
{
}

void GameManager::Scene::Update()
{
    dt = clock.restart();
    Event ev;
    InputManager::ClearInput();

    while (window->pollEvent(ev))
    {
        InputManager::UpdateInput(ev);
    }
}

void GameManager::Scene::Draw()
{
    window->clear();
}

void GameManager::Scene::Release()
{
	for (auto go : gameObjectList)
	{
		go->Release();
		delete go;
	}
	gameObjectList.clear();
}

// Title
GameManager::Title::Title()
    : Scene()
{
    Init();
}

GameManager::Title::~Title()
{
}

void GameManager::Title::Init()
{
    Scene::Init();

    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
}

void GameManager::Title::Update()
{
    Scene::Update();

    if (InputManager::GetKeyDown(Keyboard::Key::Return))
    {
        playing = false;
        return;
    }
    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
    {
        window->close();
        return;
    }

    for (auto go : gameObjectList)
    {
        go->Update(dt.asSeconds());
    }
}

void GameManager::Title::Draw()
{
    Scene::Draw();

    for (auto go : gameObjectList)
    {
        go->Draw(*window);
    }
    window->draw(*um->GetTextUI("title"));
    window->draw(*um->GetTextUI("press enter"));
    window->display();
}

void GameManager::Title::Release()
{
}