#include "Scene.h"
#include "ResourceManager.h"

Scene::Scene()
	: playing(true)
{
}

Scene::Scene(const Scene& ref)
{
}

Scene& Scene::operator=(const Scene& ref)
{
    return *this;
}

Scene::~Scene()
{
}

void Scene::Init()
{
}

void Scene::Update()
{
    dt = clock.restart();
    Event ev;
    InputManager::ClearInput();

    while (window->pollEvent(ev))
    {
        InputManager::UpdateInput(ev);
    }
}

void Scene::Draw()
{
    window->clear();
}

void Scene::Release()
{
    for (auto go : gameObjectList)
    {
        go->Release();
        delete go;
    }
    gameObjectList.clear();
}

void Scene::GetWindow(RenderWindow* _window)
{
    window = _window;
}

void Scene::GetUIManager(UIManager* _um)
{
    um = _um;
}


// Title
Title::Title()
    : Scene()
{
    Init();
}

Title::~Title()
{
}

void Title::Init()
{
    Scene::Init();

    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
}

void Title::Update()
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

void Title::Draw()
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

void Title::Release()
{
    Scene::Release();
}

// Menu
Menu::Menu(int& _gameMode)
{
    Init();
}

Menu::~Menu()
{
}

void Menu::Init()
{
    Scene::Init();

    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
}

void Menu::Update()
{
    Scene::Update();

    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
    {
        gameMode = 0;
        playing = false;
        return;
    }

    if (InputManager::GetKeyDown(Keyboard::Key::Up))
    {
        gameMode = 1;
    }

    if (InputManager::GetKeyDown(Keyboard::Key::Down))
    {
        gameMode = 2;
    }

    for (auto go : gameObjectList)
    {
        go->Update(dt.asSeconds());
    }

    if (gameMode == 1)
    {
        um->GetTextUI("arrow")->setPosition(
            { um->GetwSize().x * 0.45f, um->GetwSize().y * 0.5f });
    }
    else if (gameMode == 2)
    {
        um->GetTextUI("arrow")->setPosition(
            { um->GetwSize().x * 0.45f, um->GetwSize().y * 0.75f });
    }
}

void Menu::Draw()
{
    Scene::Draw();
    
    for (auto go : gameObjectList)
    {
        go->Draw(*window);
    }
    window->draw(*um->GetTextUI("arrow"));
    window->draw(*um->GetTextUI("Menu"));
    window->draw(*um->GetTextUI("1p"));
    window->draw(*um->GetTextUI("2p"));
    window->display();
}

void Menu::Release()
{
    Scene::Release();
}
