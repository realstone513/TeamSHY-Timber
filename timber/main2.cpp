#include "GameManager.h"
#include "Player.h"
#include "Tree.h"

#include <iostream>

int main()
{
	GameManager gm;

	while (gm.GetWindow()->isOpen())
	{
		gm.PlayScene(new Title());
		if (gm.GetScene()->Loop())
			return 0;
		gm.ReleaseScene();

		SelectGameMode* sgm = new SelectGameMode();
		gm.PlayScene(sgm);
		if (gm.GetScene()->Loop())
			continue;
		gm.gameMode = sgm->GetGameMode();
		gm.ReleaseScene();

		SelectCharacter* sc = new SelectCharacter(gm.gameMode);
		gm.PlayScene(sc);
		if (gm.GetScene()->Loop())
			continue;
		gm.character1p = sc->GetCharacter1p();
		gm.character2p = sc->GetCharacter2p();
		gm.ReleaseScene();



		//gm.GetWindow()->close();
	}
	return 0;
}

//        //Game Scene
//        if (PlayGame && (gamemode == 1 || gamemode == 2))
//        {
//            Vector2f timerBarSize(400, 80);
//            float duration = 4.0f;
//            float timer = duration;
//            bool isGameover =true;
//            um.SetRectangleUI("timer Bar", timerBarSize, Color::Red);
//            um.GetRectangleUI("timer Bar")->setPosition(
//                um.GetwSize().x * 0.5f - timerBarSize.x * 0.5f,
//                um.GetwSize().y - 100);
//            string charcterIndex[3] = { "graphics/player_green.png","graphics/player_red.png","graphics/player_yellow.png" };
//
//            if (gamemode == 1)
//            {
//                std::vector<float> startVector = { 2000, -300 };
//                std::vector<float> endVector = { -300, 2000 };
//                auto Bee = new FloatingObject(RMI->GetTexture("graphics/bee.png"));
//                auto Beeindex = rand() % 2;
//
//                Bee->Set({ 300,500 }, { 600, 800 },
//                    { startVector[Beeindex], 0 }, { endVector[Beeindex], 0 });
//                gameObjectList.push_back(Bee);
//                for (int i = 0; i < 3; ++i)
//                {
//                    auto cloud = new FloatingObject(RMI->GetTexture("graphics/cloud.png"));
//                    auto index = rand() % 2;
//
//                    cloud->Set({ 100,200 }, { 100, 200 },
//                        { startVector[index], 0 }, { endVector[index], 0 });
//                    gameObjectList.push_back(cloud);
//                }
//                Tree* tree = new Tree(RMI->GetTexture("graphics/tree.png"), gamemode, 1);
//                tree->SetPosition({ 960, 900 });
//                gameObjectList.push_back(tree);
//                Player* player1 = new Player(RMI->GetTexture(charcterIndex[onePcharcter]), gamemode, 1, tree->GetPosition());
//                gameObjectList.push_back(player1);
//
//
//                for (auto i : gameObjectList)
//                {
//                    i->Init();
//                }
//
//                while (PlayGame)
//                {
//                    Time dt = clock.restart(); //??ìŸ¾ ??…ëœ²??„ë“ƒ ??“ì»™???ê¾©ì˜± ??…ëœ²??„ë“ƒ ??“ì»™ ?Žâ‘¥??æ¹²ê³•ì¤?
//                    Event ev;
//                    InputManager::ClearInput();
//
//                    while (window.pollEvent(ev))
//                    {
//                        InputManager::UpdateInput(ev);
//                    }
//                    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
//                    {
//
//                        ready = 0;
//                        gamemode = 1;
//                        Title = true;
//                        SelectMenu = false;
//                        SelectCharacter = false;
//                        PlayGame = false;
//                        window.clear();
//                        break;
//                    }
//                    float deltaTime = dt.asSeconds();
//                    window.clear();
//                    if (isGameover)
//                    {
//                        for (auto i : gameObjectList)
//                        {
//                           i->Update(deltaTime);
//                        }
//                    }
//                    else
//                    {
//                        deltaTime = 0;
//                    }
//                    
//                    for (auto i : gameObjectList)
//                    {
//                        i->Draw(window);
//                    }
//                    if (player1->GetPlayerSide() == tree->GetCurrentBranchSide())
//                    {
//                        player1->Die();
//                        isGameover = false;
//                    }
//                    // UI update
//                    timer -= deltaTime;
//                    if (timer < 0.f)
//                    {
//                        timer = 0.f;
//                    }
//
//                    float normTime = timer / duration; // ?ëº?‡‹??
//                    float timerSizeX = timerBarSize.x * normTime;
//                    um.GetRectangleUI("timer Bar")->
//                        setSize({ timerSizeX, timerBarSize.y });
//                    um.GetRectangleUI("timer Bar")->setPosition(
//                        um.GetwSize().x * 0.5f - timerSizeX * 0.5f,
//                        um.GetwSize().y - 100);
//                    onePScore = player1->GetScore();
//                    um.SetTextUI(to_string(onePScore), "1pScore", 100, Color::Magenta);
//                    window.draw(*(um.GetTextUI("1pScore")));
//                    window.draw(*um.GetRectangleUI("timer Bar"));
//                    window.display();
//
//                }
//            }
//            else
//            {
//                Tree* tree1 = new Tree(RMI->GetTexture("graphics/2Ptree.png"), gamemode, 1);
//                tree1->SetPosition({ 480, 900 });
//                gameObjectList.push_back(tree1);
//                Tree* tree2 = new Tree(RMI->GetTexture("graphics/2Ptree.png"), gamemode, 2);
//                tree2->SetPosition({ 1440, 900 });
//                gameObjectList.push_back(tree2);
//                Player* player1 = new Player(RMI->GetTexture(charcterIndex[onePcharcter]), gamemode, 1, tree1->GetPosition());
//                gameObjectList.push_back(player1);
//                Player* player2 = new Player(RMI->GetTexture(charcterIndex[twoPcharcter]), gamemode, 2, tree2->GetPosition());
//                gameObjectList.push_back(player2);
//
//                for (auto i : gameObjectList)
//                {
//                    i->Init();
//                }
//                while (PlayGame)
//                {
//                    Time dt = clock.restart(); //??ìŸ¾ ??…ëœ²??„ë“ƒ ??“ì»™???ê¾©ì˜± ??…ëœ²??„ë“ƒ ??“ì»™ ?Žâ‘¥??æ¹²ê³•ì¤?
//                    Event ev;
//                    InputManager::ClearInput();
//
//                    while (window.pollEvent(ev))
//                    {
//                        InputManager::UpdateInput(ev);
//                    }
//                    if (InputManager::GetKeyDown(Keyboard::Key::Escape))
//                    {
//
//                        ready = 0;
//                        gamemode = 1;
//                        Title = true;
//                        SelectMenu = false;
//                        SelectCharacter = false;
//                        PlayGame = false;
//                        window.clear();
//                        break;
//                    }
//                    if (player1->GetPlayerSide() == tree1->GetCurrentBranchSide())
//                    {
//                        player1->Die();
//                        isGameover = false;
//                    }
//                    if (player2->GetPlayerSide() == tree2->GetCurrentBranchSide())
//                    {
//                        player2->Die();
//                        isGameover = false;
//                    }
//                    float deltaTime = dt.asSeconds();
//                    window.clear();
//                    if (isGameover)
//                    {
//                        for (auto i : gameObjectList)
//                        {
//                            i->Update(deltaTime);
//
//                        }
//                    }
//                    else
//                    {
//                        deltaTime = 0;
//                    }
//                    for (auto i : gameObjectList)
//                    {
//                        i->Draw(window);
//                    }
//
//                    // UI update
//                    timer -= deltaTime;
//                    if (timer < 0.f)
//                    {
//                        timer = 0.f;
//                    }
//
//                    float normTime = timer / duration; // ?ëº?‡‹??
//                    float timerSizeX = timerBarSize.x * normTime;
//                    um.GetRectangleUI("timer Bar")->
//                        setSize({ timerSizeX, timerBarSize.y });
//                    um.GetRectangleUI("timer Bar")->setPosition(
//                        um.GetwSize().x * 0.5f - timerSizeX * 0.5f,
//                        um.GetwSize().y - 100);
//
//                    onePScore = player1->GetScore();
//                    um.SetTextUI(to_string(onePScore), "1pScore", 100, Color::Magenta);
//                    window.draw(*(um.GetTextUI("1pScore")));
//
//                    twoPScore = player2->GetScore();
//                    um.SetTextUI(to_string(twoPScore), "2pScore", 100, Color::Magenta);
//                    window.draw(*(um.GetTextUI("2pScore")));
//
//                    window.draw(*um.GetRectangleUI("timer Bar"));
//
//                    window.display();
//
//                }
//            }
//        }
//        for (auto go : gameObjectList)
//        {
//            go->Release();
//            delete go;
//        }
//        gameObjectList.clear();
//    }
//    return 0;
//}