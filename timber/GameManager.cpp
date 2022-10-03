#include "GameManager.h"
#include "ResourceManager.h"

GameManager::GameManager()
{
    VideoMode vm(1920, 1080);
    window = new RenderWindow(vm, "timber", Style::Default);
    wSize = window->getSize();
    um = new UIManager(RMI->GetFont("fonts/KOMIKAP_.ttf"));
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
    
    // UI Init Setting
    um->Init();

    //Title
    (*um).SetTextUI("Press Enter to start!", "press enter");
    (*um).GetTextUI("press enter")->setPosition({ 500, 600 });
    (*um).SetTextUI("Timber!", "title", 150, Color::Yellow);
    (*um).GetTextUI("title")->setPosition({ 700, 400 });
    //Menu
    (*um).SetTextUI("Menu");
    (*um).GetTextUI("Menu")->setPosition({
        wSize.x * 0.5f, wSize.y * 0.5f });
    (*um).GetTextUI("Menu")->setPosition({ wSize.x * 0.35f, wSize.y * 0.15f });
    (*um).GetTextUI("Menu")->setCharacterSize(225);
    (*um).SetTextUI("1 player", "1p");
    (*um).GetTextUI("1p")->setPosition({ wSize.x * 0.5f, wSize.y * 0.5f });
    (*um).SetTextUI("2 players", "2p");
    (*um).GetTextUI("2p")->setPosition({ wSize.x * 0.5f, wSize.y * 0.75f });
    (*um).SetTextUI("->", "arrow");
    (*um).GetTextUI("arrow")->setPosition({ wSize.x * 0.45f, wSize.y * 0.5f });
    //Character Select
    (*um).SetTextUI("1P", "1pArrow", 100, Color::Red);
    (*um).GetTextUI("1pArrow")->setPosition({ wSize.x * 0.25f, wSize.y * 0.5f });
    (*um).SetTextUI("2P", "2pArrow", 100, Color::Green);
    (*um).GetTextUI("2pArrow")->setPosition({ wSize.x * 0.5f, wSize.y * 0.5f });
    //EndGame
    (*um).SetTextUI("Game Over", "end", 150, Color::Yellow);
    (*um).GetTextUI("end")->setPosition({ 700, 400 });
}

void GameManager::Update()
{
}

void GameManager::Draw()
{
}

void GameManager::Clear()
{
    for (auto go : gameObjectList)
    {
        go->Release();
        delete go;
    }
    gameObjectList.clear();
}

void GameManager::Release()
{
    um->Release();
    delete um;
    delete window;
}

RenderWindow* GameManager::GetWindow()
{
    return window;
}
