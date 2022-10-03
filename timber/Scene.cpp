#include "Scene.h"
#include "ResourceManager.h"

Scene::Scene()
    : playing(true), exit(false)
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

    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
    {
        playing = false;
        window->close();
        exit = true;
        return;
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

bool Scene::Loop()
{
    while (playing)
    {
        Update();
        Draw();
    }
    return exit;
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

// SelectGameMode
SelectGameMode::SelectGameMode()
    : gameMode(1)
{
    Init();
}

SelectGameMode::~SelectGameMode()
{
}

void SelectGameMode::Init()
{
    Scene::Init();

    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
}

void SelectGameMode::Update()
{
    Scene::Update();
    
    if (InputManager::GetKeyDown(Keyboard::Key::Return))
    {
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

void SelectGameMode::Draw()
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

void SelectGameMode::Release()
{
    Scene::Release();
}

int SelectGameMode::GetGameMode()
{
    return gameMode;
}

// SelectCharacter
SelectCharacter::SelectCharacter(int gameMode)
    : gameMode(gameMode), character1p(0), character2p(0), ready(0)
{
    Init();
}

SelectCharacter::~SelectCharacter()
{
}

void SelectCharacter::Init()
{
    Scene::Init();

    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
    
    list<SpriteGameObject*> charcterList;
    charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_red.png"), Vector2f(200, 400)));
    charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_green.png"), Vector2f(800, 400)));
    charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_yellow.png"), Vector2f(1400, 400)));   
    for (auto c : charcterList)
    {
        c->setScale(2, 2);
        gameObjectList.push_back(c);
    }
}

void SelectCharacter::Update()
{
    Scene::Update();

    if (gameMode == 1)
    {
        if (InputManager::GetKeyDown(Keyboard::Key::A))
		{
			character1p -= 1;
		}
		if (InputManager::GetKeyDown(Keyboard::Key::D))
		{
            character1p += 1;
		}
        if (InputManager::GetKeyDown(Keyboard::Return))
		{
            ready++;
            playing = false;
            return;
		}
    }

    if (ready)
    {
        playing = false;
        return;
    }
}

void SelectCharacter::Draw()
{
    Scene::Draw();

    for (auto go : gameObjectList)
    {
        go->Draw(*window);
    }

    if (gameMode == 1)
	{
		if (character1p == 0)
		{
			um->GetTextUI("1pArrow")->setPosition(
                { um->GetwSize().x * 0.25f, um->GetwSize().y * 0.75f });
		}
		else if (character1p == 1)
		{
			um->GetTextUI("1pArrow")->setPosition(
                { um->GetwSize().x * 0.5f, um->GetwSize().y * 0.75f });
		}
		else if (character1p == 2)
		{
			um->GetTextUI("1pArrow")->setPosition(
                { um->GetwSize().x * 0.75f,um->GetwSize().y * 0.75f });
		}
		window->draw(*um->GetTextUI("1pArrow"));
	}

    window->display();
}

void SelectCharacter::Release()
{
    Scene::Release();
}

int SelectCharacter::GetCharacter1p()
{
    return character1p;
}

int SelectCharacter::GetCharacter2p()
{
    return character2p;
}
