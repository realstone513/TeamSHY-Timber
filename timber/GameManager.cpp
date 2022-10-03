#include "GameManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

GameManager::GameManager()
    : gameMode(0)
{
    VideoMode vm(1920, 1080);
    window = new RenderWindow(vm, "timber", Style::Default);
    wSize = window->getSize();
    um = new UIManager(RMI->GetFont("fonts/KOMIKAP_.ttf"), wSize);
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
    currentScene->GetWindow(window);
    currentScene->GetUIManager(um);
}

void GameManager::ReleaseScene()
{
    currentScene->Release();
    delete currentScene;
}

RenderWindow* GameManager::GetWindow()
{
    return window;
}

Scene* GameManager::GetScene()
{
    return currentScene;
}