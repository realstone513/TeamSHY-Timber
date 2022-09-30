#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "SpriteGameObject.h"
#include <list>
#include "Player.h"
#include "InputManager.h"
#include "Tree.h"


using namespace sf;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "timber", Style::Default);
    std::list<SpriteGameObject*> gameObjectList;
    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));

    Tree* tree1 = new Tree(RMI->GetTexture("graphics/2Ptree.png"),1);
    gameObjectList.push_back(tree1);
    Tree* tree2 = new Tree(RMI->GetTexture("graphics/2Ptree.png"),2);
    gameObjectList.push_back(tree2);
    Player* player1 = new Player(RMI->GetTexture("graphics/player_green.png"),1);
    gameObjectList.push_back(player1);
    Player* player2 = new Player(RMI->GetTexture("graphics/player_red.png"),2);
    gameObjectList.push_back(player2);

    for (auto i : gameObjectList)
    {
        i->Init();
    }
    Clock clock;

    while (true)
    {
        Time dt = clock.restart(); //이전 업데이트 시간과 현재 업데이트 시간 차이 기록

        Event ev;
        InputManager::ClearInput();
        while (window.pollEvent(ev))
        {
            InputManager::UpdateInput(ev);
        }
        float deltaTime = dt.asSeconds(); //isPause ? 0.f : dt.asSeconds();
        for (auto i : gameObjectList)
        {
            i->Update(deltaTime);
        }
        for (auto i : gameObjectList)
        {
            i->Draw(window);
        }
        window.display();
    }
    
    return 0;
}


/*#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "MoveAtoBObject.h"
#include "Utils.h"
#include "InputManager.h"
#include "Player.h"
#include "ResourceManager.h"

#include <iostream>

using namespace sf;

void UpdateBranches(vector<Branch*>& branches, int& current, vector<Vector2f>& posArr)
{
    current = (current + 1) % branches.size();

    for (int i = 0; i < branches.size(); ++i)
    {
        int index = (current + i) % branches.size();
        branches[index]->SetPosition(posArr[i]);
        if (i == branches.size() - 1)
        {
            branches[index]->SetSide((Sides)Utils::Range(0, 2));
        }
    }
}

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "timber", Style::Default);
    Vector2u size = window.getSize();

    std::list<SpriteGameObject*> gameObjectList;
    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));

    Sound timeOutSound;
    timeOutSound.setBuffer(RMI->GetSoundBuffer("sound/out_of_time.wav"));
    timeOutSound.setVolume(25.f);
    
    std::vector<float> startVector = { 2000, -300 };
    std::vector<float> endVector = { -300, 2000 };
    for (int i = 0; i < 3; i++)
    {
        auto movingObj = new MoveAtoBObject(
            RMI->GetTexture("graphics/cloud.png"));
        auto index = rand() % 2;

        movingObj->Set({ 200,400 }, { 100, 400 },
            { startVector[index], 0 }, { endVector[index], 0 });
        gameObjectList.push_back(movingObj);
    }

    SpriteGameObject* tree = new SpriteGameObject(
        RMI->GetTexture("graphics/tree.png"),
        Vector2f(size.x * 0.5f, 900));
    tree->SetOrigin(Origins::BC);
    gameObjectList.push_back(tree);

    for (int i = 0; i < 5; i++)
    {
        MoveAtoBObject* movingObj = new MoveAtoBObject(
            RMI->GetTexture("graphics/bee.png"));
        movingObj->Set({ 200,400 }, { 500, 1000 }, { 2000, 0 }, { -100, 0 });
        gameObjectList.push_back(movingObj);
    }  

    // Init Branch
    vector<Branch*> branches(6);
    for (int i = 0; i < branches.size(); i++)
    {
        branches[i] = new Branch(
            RMI->GetTexture("graphics/branch.png"), tree);
        if (i == 0)
            branches[i]->SetSide(Sides::None);
        else
            branches[i]->SetSide((Sides)Utils::Range(0, 2));
        gameObjectList.push_back(branches[i]);
    }

    Player* player = new Player(
        RMI->GetTexture("graphics/player.png"));
    gameObjectList.push_back(player);
    player->Set(tree->GetPosition());

    // gameObject를 전부 추가한 후 Init.
    for (auto go : gameObjectList)
    {
        go->Init();
    }

    int currentBranch = -1;
    vector<Vector2f> branchPosArr(branches.size());
    float x = branches[0]->GetPosition().x;
    float y = 800;
    float offset = branches[0]->GetSize().y;
    offset += 100;
    for (int i = 0; i < branches.size(); ++i)
    {
        branchPosArr[i] = Vector2f(x, y);
        y -= offset;
    }
    UpdateBranches(branches, currentBranch, branchPosArr);

    // UI OBJ CREATES
    Text messageText;
    messageText.setFont(RMI->GetFont("fonts/KOMIKAP_.ttf"));
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to start!");
    messageText.setPosition(size.x * 0.5f, size.y * 0.5f);
    Utils::SetOrigin(messageText, Origins::MC);

    Text scoreText;
    scoreText.setFont(RMI->GetFont("fonts/KOMIKAP_.ttf"));
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(Color::White);

    String scoreString = "Score: " + to_string(player->GetScore());
    scoreText.setString(scoreString);
    scoreText.setPosition(20, 20);
    Utils::SetOrigin(scoreText, Origins::TL);

    Vector2f timerBarSize(400, 80);
    RectangleShape timerBar;
    timerBar.setSize(timerBarSize);
    timerBar.setFillColor(Color::Red);
    timerBar.setPosition(
        size.x * 0.5f - timerBarSize.x * 0.5f,
        size.y - 100);

    float duration = 5.f;
    float timer = duration;

    Text timerText;
    timerText.setFont(RMI->GetFont("fonts/KOMIKAP_.ttf"));
    timerText.setCharacterSize(50);
    timerText.setFillColor(Color::White);
    string timerString = to_string(timer);
    timerString = timerString.substr(0, 4);
    timerText.setString(timerString);
    timerText.setPosition(size.x * 0.5f, size.y - 50);
    Utils::SetOrigin(timerText, Origins::BC);

    bool isPause = true;
    bool isGameOver = false;

    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart(); //이전 업데이트 시간과 현재 업데이트 시간 차이 기록

        Event ev;
        InputManager::ClearInput();
        while (window.pollEvent(ev))
        {
            InputManager::UpdateInput(ev);
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))  //static 함수
        {
            window.close();
            continue;
        }

        if (InputManager::GetKeyDown(Keyboard::Return))
        {
            if (isGameOver)
            {
                messageText.setString("Press Enter to start!");
                Utils::SetOrigin(messageText, Origins::MC);
                isGameOver = !isGameOver;
                timer = duration;
                player->Clear();

                for (auto go : gameObjectList)
                {
                    go->Init();
                }

                x = branches[currentBranch]->GetPosition().x;
                y = 800;
                offset = branches[currentBranch]->GetSize().y;
                offset += 100;
                for (int i = 0; i < branches.size(); ++i)
                {
                    branchPosArr[i] = Vector2f(x, y);
                    y -= offset;
                }
                UpdateBranches(branches, currentBranch, branchPosArr);
                branches[currentBranch]->SetSide(Sides::None);
                // 게임 시작할 때 했던 모든 사전작업을 다시 할 수 있게 함
            }
            else
                isPause = !isPause;
        }
        
        size = window.getSize();
        float deltaTime = isPause ? 0.f : dt.asSeconds();

        // UI update
        timer -= deltaTime;
        if (timer < 0.f)
        {
            timeOutSound.play();
            timer = 0.f;
            messageText.setString("Game Over!!");
            Utils::SetOrigin(messageText, Origins::MC);
            isPause = true;
            isGameOver = true;
        }

        float normTime = timer / duration; // 정규화
        float timerSizeX = timerBarSize.x * normTime;
        timerBar.setSize({ timerSizeX, timerBarSize.y });
        timerBar.setPosition
        (size.x * 0.5f - timerSizeX * 0.5f, size.y - 100);

        timerString = to_string(timer);
        timerString = timerString.substr(0, 4);
        timerText.setString(timerString);

        // Update
        if (!isPause)
        {
            for (auto go : gameObjectList)
            {
                go->Update(deltaTime);
            }
            if (InputManager::GetKeyDown(Keyboard::Key::Left) ||
                InputManager::GetKeyDown(Keyboard::Key::Right))
            {
                UpdateBranches(branches, currentBranch, branchPosArr);
                if (player->GetPos() == branches[currentBranch]->GetSide())
                {
                    player->Die();
                    messageText.setString("Game Over!!");
                    Utils::SetOrigin(messageText, Origins::MC);
                    isPause = true;
                    isGameOver = true;
                }
                timer += 0.2f;
            }
        }

        // Draw      
        window.clear();
        for (auto go : gameObjectList)
        {
            go->Draw(window);
        }

        if (isPause)
        {
            window.draw(messageText);
        }

        scoreText.setString(
            String("Score: " + to_string(player->GetScore())));
        window.draw(scoreText);
        window.draw(timerBar);
        window.draw(timerText);
 
        window.display();
    }     

    for (auto go : gameObjectList)
    {
        go->Release();
        delete go;
    }
    gameObjectList.clear();
    
    return 0;
}*/