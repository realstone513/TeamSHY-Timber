#include <vector>
#include <string>
#include "Scene.h"
#include "ResourceManager.h"
#include "FloatingObject.h"

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

    gameObjectList.push_back(new SpriteGameObject(PRMI->GetTexture("graphics/background.png")));
    
    vector<float> startVector = { 2000, -300 };
    vector<float> endVector = { -300, 2000 };
    for (int i = 0; i < 3; ++i)
    {
        auto cloud = new FloatingObject(PRMI->GetTexture("graphics/cloud.png"));
        auto index = rand() % 2;

        cloud->Set({ 100, 200 }, { 100, 200 },
            { startVector[index], 0 }, { endVector[index], 0 });
        gameObjectList.push_back(cloud);
    }
    auto Bee = new FloatingObject(PRMI->GetTexture("graphics/bee.png"));
    auto Beeindex = rand() % 2;

    Bee->Set({ 300, 500 }, { 600, 800 },
        { startVector[Beeindex], 0 }, { endVector[Beeindex], 0 });
    gameObjectList.push_back(Bee);

    for (auto i : gameObjectList)
    {
        i->Init();
    }
}

void Title::Update()
{
    Scene::Update();

    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
    {
        playing = false;
        window->close();
        exit = true;
        return;
    }

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
    window->draw(*um->GetTextUI("team name"));
    window->draw(*um->GetTextUI("press enter"));
    window->draw(*um->GetTextUI("title"));
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

    gameObjectList.push_back(new SpriteGameObject(PRMI->GetTexture("graphics/background.png")));
}

void SelectGameMode::Update()
{
    Scene::Update();

    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
    {
        playing = false;
        exit = true;
        return;
    }

    if (InputManager::GetKeyDown(Keyboard::Key::Return))
    {
        playing = false;
        return;
    }

    if (InputManager::GetKeyDown(Keyboard::Key::Up) || 
        InputManager::GetKeyDown(Keyboard::Key::W))
    {
        gameMode = 1;
    }

    if (InputManager::GetKeyDown(Keyboard::Key::Down) ||
        InputManager::GetKeyDown(Keyboard::Key::S))
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
            { um->GetwSize().x * 0.3f, um->GetwSize().y * 0.5f });
    }
    else if (gameMode == 2)
    {
        um->GetTextUI("arrow")->setPosition(
            { um->GetwSize().x * 0.3f, um->GetwSize().y * 0.65f });
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
    window->draw(*um->GetTextUI("Game Mode"));
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
    : gameMode(gameMode), character1p(0), character2p(0), ready1p(false), ready2p(false)
{
    Init();
}

SelectCharacter::~SelectCharacter()
{
}

void SelectCharacter::Init()
{
    Scene::Init();

    gameObjectList.push_back(new SpriteGameObject(PRMI->GetTexture("graphics/background.png")));
    
    list<SpriteGameObject*> charcterList;
    charcterList.push_back(new SpriteGameObject(PRMI->GetTexture("graphics/player_red.png"), Vector2f(200, 400)));
    charcterList.push_back(new SpriteGameObject(PRMI->GetTexture("graphics/player_green.png"), Vector2f(800, 400)));
    charcterList.push_back(new SpriteGameObject(PRMI->GetTexture("graphics/player_yellow.png"), Vector2f(1400, 400)));   
    for (auto c : charcterList)
    {
        c->setScale(2, 2);
        gameObjectList.push_back(c);
    }
}

void SelectCharacter::Update()
{
    Scene::Update();

    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
    {
        playing = false;
        exit = true;
        return;
    }

    if (gameMode == 1) // 1P
    {
        if (InputManager::GetKeyDown(Keyboard::Key::A))
		{
            if (character1p > 0)
			    character1p -= 1;
		}
		if (InputManager::GetKeyDown(Keyboard::Key::D))
		{
            if (character1p < 2)
                character1p += 1;
		}
        if (InputManager::GetKeyDown(Keyboard::Return))
		{
            playing = false;
            return;
		}
    }
    else // 2P
    {
        if (InputManager::GetKeyDown(Keyboard::Key::A) && character1p > 0)
		{
            if (character1p > 0)
            {
                character1p -= 1;
                ready1p = false;
            }
		}
		if (InputManager::GetKeyDown(Keyboard::Key::D) && character1p < 2)
		{
            if (character1p < 2)
            {
                character1p += 1;
                ready1p = false;
            }
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Left) && character2p > 0)
		{
            if (character2p > 0)
            {
                character2p -= 1;
                ready2p = false;
            }
		}
		if (InputManager::GetKeyDown(Keyboard::Key::Right) && character2p < 2)
		{
            if (character2p < 2)
            {
                character2p += 1;
                ready2p = false;
            }
		}
        if (InputManager::GetKeyDown(Keyboard::Space))
        {
            ready1p = true;
        }
        if (InputManager::GetKeyDown(Keyboard::Return))
        {
            ready2p = true;
        }

        if (ready1p && ready2p)
        {
            playing = false;
            return;
        }
    }
}

void SelectCharacter::Draw()
{
    Scene::Draw();

    for (auto go : gameObjectList)
    {
        go->Draw(*window);
    }

    if (gameMode == 1) // 1P
	{
        Vector2f position;
		if (character1p == 0)
		{
            position = { um->GetwSize().x * 0.2f, um->GetwSize().y * 0.75f };
		}
		else if (character1p == 1)
		{
            position = { um->GetwSize().x * 0.5f, um->GetwSize().y * 0.75f };
		}
		else if (character1p == 2)
		{
            position = { um->GetwSize().x * 0.8f, um->GetwSize().y * 0.75f };
		}
        um->GetTextUI("1pArrow")->setPosition(position);
		window->draw(*um->GetTextUI("1pArrow"));
	}
    else // 2P
    {
        Vector2f position1p;
        Vector2f ready1p;
		if (character1p == 0)
		{
            position1p = { um->GetwSize().x * 0.2f, um->GetwSize().y * 0.75f };
            ready1p = { um->GetwSize().x * 0.1f, um->GetwSize().y * 0.50f };
		}
		else if (character1p == 1)
		{
            position1p = { um->GetwSize().x * 0.5f, um->GetwSize().y * 0.75f };
            ready1p = { um->GetwSize().x * 0.4f, um->GetwSize().y * 0.50f };
		}
		else if (character1p == 2)
		{
            position1p = { um->GetwSize().x * 0.8f, um->GetwSize().y * 0.75f };
            ready1p = { um->GetwSize().x * 0.7f, um->GetwSize().y * 0.50f };
		}
        um->GetTextUI("1pArrow")->setPosition(position1p);
        um->GetTextUI("1pReady")->setPosition(ready1p);

        Vector2f position2p;
        Vector2f ready2p;
		if (character2p == 0)
		{
            position2p = { um->GetwSize().x * 0.2f, um->GetwSize().y * 0.75f };
            ready2p = { um->GetwSize().x * 0.1f, um->GetwSize().y * 0.50f };
		}
		else if (character2p == 1)
		{
            position2p = { um->GetwSize().x * 0.5f, um->GetwSize().y * 0.75f };
            ready2p = { um->GetwSize().x * 0.4f, um->GetwSize().y * 0.50f };
		}
		else if (character2p == 2)
		{
            position2p = { um->GetwSize().x * 0.8f, um->GetwSize().y * 0.75f };
            ready2p = { um->GetwSize().x * 0.7f, um->GetwSize().y * 0.50f };
		}
        um->GetTextUI("2pArrow")->setPosition(position2p);
        um->GetTextUI("2pReady")->setPosition(ready2p);

		window->draw(*um->GetTextUI("1pArrow"));
		window->draw(*um->GetTextUI("2pArrow"));
    }
    if (gameMode == 2)
    {
        window->draw(*um->GetTextUI("add1"));
        window->draw(*um->GetTextUI("minus1"));
        window->draw(*um->GetTextUI("add2"));
        window->draw(*um->GetTextUI("minus2"));
        window->draw(*um->GetTextUI("add3"));
        window->draw(*um->GetTextUI("minus3"));
    }

    window->draw(*um->GetTextUI("Select"));
    if (ready1p)
        window->draw(*um->GetTextUI("1pReady"));
    if (ready2p)
        window->draw(*um->GetTextUI("2pReady"));
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

// GamePlay
GamePlay::GamePlay(int _mode, int player1, int player2)
    : gameMode(_mode), character1p(player1), character2p(player2), gameOver(false), pause(false)
{
    // 타이머 바 크기 조절에 필요한 값
    timerBarSize = { 400, 80 };
    // 난이도에 필요한 두 값
    duration = gameMode == 1 ? 5.f : 25.f;
    bonusTime = 0.25f;

    timer = duration;

    timeOutSound.setBuffer(PRMI->GetSoundBuffer("sound/out_of_time.wav"));
    timeOutSound.setVolume(50);
    Init();
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    Scene::Init();

    gameObjectList.push_back(new SpriteGameObject(PRMI->GetTexture("graphics/background.png")));
    
    vector<float> startVector = { 2000, -300 };
    vector<float> endVector = { -300, 2000 };
    for (int i = 0; i < 3; ++i)
    {
        auto cloud = new FloatingObject(PRMI->GetTexture("graphics/cloud.png"));
        auto index = rand() % 2;

        cloud->Set({ 100, 200 }, { 100, 200 },
            { startVector[index], 0 }, { endVector[index], 0 });
        gameObjectList.push_back(cloud);
    }

    string charcterIndex[3] = {
        "graphics/player_red.png",
        "graphics/player_green.png",
        "graphics/player_yellow.png" };
    if (gameMode == 1) // 1P
    {
        tree1 = new Tree(PRMI->GetTexture("graphics/tree.png"), gameMode, 1);
        tree1->SetPosition({ 960, 900 });
        gameObjectList.push_back(tree1);
        player1 = new Player(PRMI->GetTexture(charcterIndex[character1p]), gameMode, 1, tree1->GetPosition(), PRMI->GetTexture("graphics/axe.png"), character1p);
        gameObjectList.push_back(player1);
    }
    else // 2P
    {
        tree1 = new Tree(PRMI->GetTexture("graphics/2Ptree.png"), gameMode, 1);
		tree1->SetPosition({ 480, 900 });
		gameObjectList.push_back(tree1);
		tree2 = new Tree(PRMI->GetTexture("graphics/2Ptree.png"), gameMode, 2);
		tree2->SetPosition({ 1440, 900 });
		gameObjectList.push_back(tree2);
		player1 = new Player(PRMI->GetTexture(charcterIndex[character1p]), gameMode, 1, tree1->GetPosition(), PRMI->GetTexture("graphics/axe.png"), character1p);
		gameObjectList.push_back(player1);
		player2 = new Player(PRMI->GetTexture(charcterIndex[character2p]), gameMode, 2, tree2->GetPosition(), PRMI->GetTexture("graphics/axe.png"), character2p);
		gameObjectList.push_back(player2);
    }

    auto Bee = new FloatingObject(PRMI->GetTexture("graphics/bee.png"));
    auto Beeindex = rand() % 2;

    Bee->Set({ 300, 500 }, { 600, 800 },
        { startVector[Beeindex], 0 }, { endVector[Beeindex], 0 });
    gameObjectList.push_back(Bee);

	for (auto i : gameObjectList)
	{
		i->Init();
	}
}

void GamePlay::Update()
{
    Scene::Update();

    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
    {
        playing = false;
        exit = true;
        return;
    }

    float deltaTime = pause || gameOver ? 0 : dt.asSeconds();
    if (!gameOver)
    {
        if (!pause)
        {
            for (auto i : gameObjectList)
            {
                i->Update(deltaTime);
            }
        }
        if (InputManager::GetKeyDown(Keyboard::Key::Return))
        {
            pause = !pause;
        }
    }

    timer -= deltaTime;
    // Game Over
    if (timer < 0.f)
    {
        timer = 0.f;
        gameOver = true;
        timeOutSound.play();
    }
    if (gameOver || pause)
        return;

    if (gameMode == 1) // 1P
    {
        if (InputManager::GetKeyDown(Keyboard::Key::A) ||
            InputManager::GetKeyDown(Keyboard::Key::D))
            timer += bonusTime;
        if ((player1->GetPlayerSide() == tree1->GetCurrentBranchSide()))
        {
            player1->Die();
            gameOver = true;
        }
    }
    else // 2P
    {
        if (player1->GetPlayerSide() == tree1->GetCurrentBranchSide())
		{
			player1->SetScoreStatus();
		}
		if (player2->GetPlayerSide() == tree2->GetCurrentBranchSide())
		{
			player2->SetScoreStatus();
		}
    }

    float normTime = timer / duration; // normalize
    float timerSizeX = timerBarSize.x * normTime;
    um->GetRectangleUI("timer Bar")->
        setSize({ timerSizeX, timerBarSize.y });
    um->GetRectangleUI("timer Bar")->setPosition(
        um->GetwSize().x * 0.5f - timerSizeX * 0.5f,
        um->GetwSize().y - 100);

    um->GetTextUI("1pScore")->setString("Score: " + to_string(player1->GetScore()));
    if (gameMode == 2)
        um->GetTextUI("2pScore")->setString("Score: " + to_string(player2->GetScore()));
}

void GamePlay::Draw()
{
    Scene::Draw();

    for (auto go : gameObjectList)
    {
        go->Draw(*window);
    }
    if (pause)
    {
        window->draw(*(um->GetTextUI("press enter")));
    }
    if (gameOver)
    {
        if (gameMode == 1)
            window->draw(*(um->GetTextUI("end")));
        else
        {
            if (player1->GetScore() > player2->GetScore())
                window->draw(*(um->GetTextUI("1PWin")));
            else if (player1->GetScore() < player2->GetScore())
                window->draw(*(um->GetTextUI("2PWin")));
            else
                window->draw(*(um->GetTextUI("draw")));
        }
    }

    window->draw(*(um->GetTextUI("1pScore")));
    if (gameMode == 2)
        window->draw(*(um->GetTextUI("2pScore")));
    window->draw(*(um->GetRectangleUI("timer Bar")));

    string timerText = to_string(timer).substr(0, 4);
    um->GetTextUI("timer Text")->setString(timerText);
    window->draw(*(um->GetTextUI("timer Text")));
    window->display();
}

void GamePlay::Release()
{
    Scene::Release();
}