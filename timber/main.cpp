#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "SpriteGameObject.h"
#include "Player.h"
#include "Tree.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "UIManager.h"

#define X 1920
#define Y 1080

using namespace std;
using namespace sf;

int main()
{
   
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "timber", Style::Default);
    list<SpriteGameObject*> gameObjectList;
    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
    Vector2u size = window.getSize();
    
    //charcter Menu
    list<SpriteGameObject*> charcterList;
    charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_green.png"), Vector2f(200, 400)));
    charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_red.png"), Vector2f(800, 400)));
    charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_yellow.png"), Vector2f(1400, 400)));
    for ( auto i : charcterList )
    {
        i->setScale(2, 2);
    }
   
    //UI
    UIManager um(RMI->GetFont("fonts/KOMIKAP_.ttf"));
    //Title
    um.SetTextUI("Press Enter to start!", "press enter");
    um.GetTextUI("press enter")->setPosition({ 500, 600 });
    um.SetTextUI("Timber!", "title", 150, Color::Yellow);
    um.GetTextUI("title")->setPosition({ 700, 400 });
    //Menu
    um.SetTextUI("Menu");
    um.GetTextUI("Menu")->setPosition({ size.x * 0.35f, size.y * 0.15f });
    um.GetTextUI("Menu")->setCharacterSize(225);
    um.SetTextUI("1 player", "1p");
    um.GetTextUI("1p")->setPosition({ size.x * 0.5f, size.y * 0.5f });
    um.SetTextUI("2 players", "2p");
    um.GetTextUI("2p")->setPosition({ size.x * 0.5f, size.y * 0.75f });
    um.SetTextUI("->", "arrow");
    um.GetTextUI("arrow")->setPosition({ size.x * 0.45f, size.y * 0.5f });
    //Character Select
    um.SetTextUI("^", "1pArrow", 100, Color::Red);
    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.25f, size.y * 0.5f });
    um.SetTextUI("^", "2pArrow", 100, Color::Green);
    um.GetTextUI("2pArrow")->setPosition({ size.x * 0.5f, size.y * 0.5f });

    //instance
    Clock clock;
    //game 분기
    bool Title = true;
    bool SelectMenu = false;
    bool SelectCharacter = false;
    bool PlayGame = false;
    
    int gamemode = 1;
    int onePcharcter = 0;
    int twoPcharcter = 0;
    int ready = 0;

    while ( window.isOpen() )
    {
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

            window.draw(*(um.GetTextUI("title")));
            window.draw(*(um.GetTextUI("press enter")));
            window.display();
        }

        //Menu Scene
        while ( SelectMenu )
        {
            Time dt = clock.restart();
            Event ev;
            InputManager::ClearInput();
            while ( window.pollEvent(ev) )
            {
                InputManager::UpdateInput(ev);
            }

            if ( InputManager::GetKeyDown(Keyboard::Key::Escape) )
            {
                //gamemode = 0;
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
            if ( InputManager::GetKeyDown(Keyboard::Return) && gamemode != 0 )
            {

                SelectMenu = false;
                SelectCharacter = true;
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
                um.GetTextUI("arrow")->setPosition({ size.x * 0.45f, size.y * 0.5f });
            }
            else if( gamemode == 2 )
            {
                um.GetTextUI("arrow")->setPosition({ size.x * 0.45f, size.y * 0.75f });
            }
            window.draw(*um.GetTextUI("arrow"));
            window.draw(*um.GetTextUI("Menu"));
            window.draw(*(um.GetTextUI("1p")));
            window.draw(*(um.GetTextUI("2p")));
            window.display();
        }

        //Character select
        while ( SelectCharacter )
        {
            Time dt = clock.restart();
            Event ev;
            InputManager::ClearInput();
            while ( window.pollEvent(ev) )
            {
                InputManager::UpdateInput(ev);
            }

            if ( InputManager::GetKeyDown(Keyboard::Key::Escape) )
            {
                if ( ready > 0 )
                {
                    ready -= 1;
                    PlayGame = false;
                    continue;
                }
                else
                {
                    SelectCharacter = false;
                    SelectMenu = true;
                    onePcharcter = 0;
                    twoPcharcter = 0;
                }
                
            }
            if ( gamemode == 1 )
            {
                if ( InputManager::GetKeyDown(Keyboard::Key::A) && onePcharcter > 0 )
                {
                    onePcharcter -= 1;
                }
                if ( InputManager::GetKeyDown(Keyboard::Key::D) && onePcharcter < 2 )
                {
                    onePcharcter += 1;
                }
            }
            else if(gamemode == 2)
            {
                if ( InputManager::GetKeyDown(Keyboard::Key::A) && onePcharcter > 0 )
                {
                    onePcharcter -= 1;
                }
                if ( InputManager::GetKeyDown(Keyboard::Key::D) && onePcharcter < 2 )
                {
                    onePcharcter += 1;
                }
                if ( InputManager::GetKeyDown(Keyboard::Key::Left) && twoPcharcter > 0 )
                {
					twoPcharcter -= 1;
                }
                if ( InputManager::GetKeyDown(Keyboard::Key::Right) && twoPcharcter < 2 )
                {
					twoPcharcter += 1;   
                }
            }
            
            if ( InputManager::GetKeyDown(Keyboard::Return) && gamemode != 0 )
            {
                ready += 1;
                if ( gamemode == 1 && ready == 1 )
                {
                    SelectCharacter = false;
                    PlayGame = true;
                }
                else if ( gamemode == 2 && ready == 2 )
                {
                    SelectCharacter = false;
                    PlayGame = true;
                }
                
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
			for ( auto go : charcterList )
			{
				go->Draw(window);
			}

            if ( gamemode == 1 )
            {
                if ( onePcharcter == 0 )
                {
                    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.25f, size.y * 0.75f });
                }
                else if ( onePcharcter == 1 )
                {
                    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.5f, size.y * 0.75f });
                }
                else if ( onePcharcter == 2 )
                {
                    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.75f, size.y * 0.75f });
                }
                window.draw(*(um.GetTextUI("1pArrow")));
            }
            else if ( gamemode == 2 )
            {
                if ( onePcharcter == 0 )
                {
                    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.25f, size.y * 0.75f });
                }
                else if ( onePcharcter == 1 )
                {
                    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.5f, size.y * 0.75f });
                }
                else if ( onePcharcter == 2 )
                {
                    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.75f, size.y * 0.75f });
                }

                if ( twoPcharcter == 0 )
                {
                    um.GetTextUI("2pArrow")->setPosition({ size.x * 0.25f, size.y * 0.75f });
                }
                else if ( twoPcharcter == 1 )
                {
                    um.GetTextUI("2pArrow")->setPosition({ size.x * 0.5f, size.y * 0.75f });
                }
                else if ( twoPcharcter == 2 )
                {
                    um.GetTextUI("2pArrow")->setPosition({ size.x * 0.75f, size.y * 0.75f });
                }
                window.draw(*(um.GetTextUI("1pArrow")));
                window.draw(*(um.GetTextUI("2pArrow")));
            }
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
                if ( InputManager::GetKeyDown(Keyboard::Key::Escape) )
                {
                    ready = 0;
                    gamemode = 1;
                    Title = true;
                    SelectMenu = false;
                    SelectCharacter = false;
                    PlayGame = false;
                    window.clear();
                }
                float deltaTime = dt.asSeconds(); //isPause ? 0.f : dt.asSeconds();
                window.clear();
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