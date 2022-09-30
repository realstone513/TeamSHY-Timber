#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "ResourceManager.h"
#include "SpriteGameObject.h"
#include "Player.h"
#include "InputManager.h"
#include "Tree.h"

#define X 1920
#define Y 1080

using namespace std;
using namespace sf;

//int main()
//{
//    VideoMode vm(1920, 1080);
//    RenderWindow window(vm, "timber", Style::Default);
//    std::list<SpriteGameObject*> gameObjectList;
//    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
//    int gamemode;
//    cin >> gamemode;
//    if (gamemode ==1)
//    {
//        Tree* tree = new Tree(RMI->GetTexture("graphics/tree.png"), gamemode, 1);
//        tree->SetPosition({ 960, 900 });
//        gameObjectList.push_back(tree);
//        Player* player1 = new Player(RMI->GetTexture("graphics/player_green.png"), gamemode, 1, tree->GetPosition());
//        gameObjectList.push_back(player1);
//    }
//    else
//    {
//        Tree* tree1 = new Tree(RMI->GetTexture("graphics/2Ptree.png"), gamemode, 1);
//        tree1->SetPosition({ 480, 900 });
//        gameObjectList.push_back(tree1);
//        Tree* tree2 = new Tree(RMI->GetTexture("graphics/2Ptree.png"), gamemode, 2);
//        tree2->SetPosition({ 1440, 900 });
//        gameObjectList.push_back(tree2);
//        Player* player1 = new Player(RMI->GetTexture("graphics/player_green.png"), gamemode, 1, tree1->GetPosition());
//        gameObjectList.push_back(player1);
//        Player* player2 = new Player(RMI->GetTexture("graphics/player_red.png"), gamemode, 2, tree2->GetPosition());
//        gameObjectList.push_back(player2);
//    }
//   
//
//    for (auto i : gameObjectList)
//    {
//        i->Init();
//    }
//    Clock clock;
//
//    while (true)
//    {
//        Time dt = clock.restart(); //이전 업데이트 시간과 현재 업데이트 시간 차이 기록
//
//        Event ev;
//        InputManager::ClearInput();
//        while (window.pollEvent(ev))
//        {
//            InputManager::UpdateInput(ev);
//        }
//        float deltaTime = dt.asSeconds(); //isPause ? 0.f : dt.asSeconds();
//        for (auto i : gameObjectList)
//        {
//            i->Update(deltaTime);
//        }
//        for (auto i : gameObjectList)
//        {
//            i->Draw(window);
//        }
//        window.display();
//    }
//    
//    return 0;
//}

int main()
{
    //Vector2u windowSize = window.getSize();
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "timber", Style::Default);
	list<SpriteGameObject*> gameObjectList;
    auto resourceMgr = ResourceManager::GetInstance();
    
    gameObjectList.push_back(new SpriteGameObject(*resourceMgr->GetTexture("graphics/background.png")));
    //

    //Font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(75);
    messageText.setFillColor(Color::White);
    messageText.setString("Press Enter to start!");
    Vector2u size = window.getSize();
    // messageText.setPosition(size.x * 0.5f, size.y * 0.5f);
    //
    Text menuText;
    menuText.setFont(font);
    menuText.setCharacterSize(75);
    menuText.setFillColor(Color::White);
    menuText.setString("Menu");
    menuText.setPosition(size.x * 0.5f, size.y * 0.5f);
    //

    Clock clock;
    bool SelectMenu = false;
    bool PlayGame = false;
    bool Title = true;
    bool run = true;
    int gamemode = 0;

    while ( window.isOpen() )
    {
        //sceneManager.Init();
        Time dt = clock.restart();
        Event ev;

        //Title Scene
        while ( Title )
        {
            Time dt = clock.restart();
            Event ev;
            InputManager::ClearInput();

            while ( window.pollEvent(ev) )
            {
                InputManager::UpdateInput(ev);
            }

            if ( InputManager::GetKeyDown(Keyboard::Key::Return) )
            {
                SelectMenu = true;
                Title = false;
                break;
            }
            if ( InputManager::GetKeyDown(Keyboard::Key::Escape) )
            {
                window.close();
                break;
            }

            float deltaTime = dt.asSeconds();

            //Update
            for ( auto go : gameObjectList )
            {

                go->Update(deltaTime);
            }

            //Draw
            window.clear();
            for ( auto go : gameObjectList )
            {
                go->Draw(window);
            }
            window.draw(messageText);
            window.display();
        }


        //Menu Scene
        while ( SelectMenu )
        {
            cout << "menu" << endl;
            Time dt = clock.restart();
            Event ev;
            InputManager::ClearInput();
            while ( window.pollEvent(ev) )
            {
                InputManager::UpdateInput(ev);
            }

            if ( InputManager::GetKeyDown(Keyboard::Key::Escape) )
            {
                SelectMenu = false;
                Title = true;
            }
            if ( InputManager::GetKeyDown(Keyboard::Key::Up) )
            {
                gamemode = 1;
            }
            if ( InputManager::GetKeyDown(Keyboard::Key::Down) )
            {
                gamemode = 2;
            }
            //Menu()
            if ( Keyboard::isKeyPressed(Keyboard::Return) && gamemode != 0 )
            {

                SelectMenu = false;
                PlayGame = true;
            }


            float deltaTime = dt.asSeconds();

            //Update
            for ( auto go : gameObjectList )
            {

                go->Update(deltaTime);
            }

            //Draw
            window.clear();
            for ( auto go : gameObjectList )
            {
                go->Draw(window);
            }
            if ( gamemode == 1 )
            {
                menuText.setString("1P");
            }
            else if( gamemode == 2 )
            {
                menuText.setString("2P");
            }
            else
            {
                menuText.setString("Menu");
            }
            window.draw(menuText);
            window.display();
        }

        //Game Scene
        if( PlayGame && (gamemode == 1 || gamemode == 2))
        {
            if ( gamemode == 1 )
			{
				Tree* tree = new Tree(RMI->GetTexture("graphics/tree.png"), gamemode, 1);
				tree->SetPosition({ 960, 900 });
				gameObjectList.push_back(tree);
				Player* player1 = new Player(RMI->GetTexture("graphics/player_green.png"), gamemode, 1, tree->GetPosition());
				gameObjectList.push_back(player1);
			}
			else
			{
				Tree* tree1 = new Tree(RMI->GetTexture("graphics/2Ptree.png"), gamemode, 1);
				tree1->SetPosition({ 480, 900 });
				gameObjectList.push_back(tree1);
				Tree* tree2 = new Tree(RMI->GetTexture("graphics/2Ptree.png"), gamemode, 2);
				tree2->SetPosition({ 1440, 900 });
				gameObjectList.push_back(tree2);
				Player* player1 = new Player(RMI->GetTexture("graphics/player_green.png"), gamemode, 1, tree1->GetPosition());
				gameObjectList.push_back(player1);
				Player* player2 = new Player(RMI->GetTexture("graphics/player_red.png"), gamemode, 2, tree2->GetPosition());
				gameObjectList.push_back(player2);
			}
            for ( auto i : gameObjectList )
			{
				i->Init();
			}
            while ( PlayGame )
            {
                Time dt = clock.restart(); //이전 업데이트 시간과 현재 업데이트 시간 차이 기록

                Event ev;
                InputManager::ClearInput();
                while ( window.pollEvent(ev) )
                {
                    InputManager::UpdateInput(ev);
                }
                float deltaTime = dt.asSeconds(); //isPause ? 0.f : dt.asSeconds();
                for ( auto i : gameObjectList )
                {
                    i->Update(deltaTime);
                }
                for ( auto i : gameObjectList )
                {
                    i->Draw(window);
                }
                window.display();
            }
           
        }       
    }
    for ( auto go : gameObjectList )
    {
        go->Release();
        delete go;
    }
    gameObjectList.clear();
    return 0;
}