#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "SpriteGameObject.h"
#include "Player.h"
#include "Tree.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "UIManager.h"
//#include "SceneManager.h"

using namespace std;
using namespace sf;

int main()
{
    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "timber", Style::Default);
    list<SpriteGameObject*> gameObjectList;
    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
    UIManager um(RMI->GetFont("fonts/KOMIKAP_.ttf"), window.getSize());

    Vector2u size = window.getSize();

    //Title
    um.SetTextUI("Press Enter to start!", "press enter");
    um.GetTextUI("press enter")->setPosition({ 500, 600 });
    um.SetTextUI("Timber!", "title", 150, Color::Yellow);
    um.GetTextUI("title")->setPosition({ 700, 400 });
    //Menu
    um.SetTextUI("Menu");
    um.GetTextUI("Menu")->setPosition({
        um.GetwSize().x * 0.5f, um.GetwSize().y * 0.5f });
    um.GetTextUI("Menu")->setPosition({ size.x * 0.35f, size.y * 0.15f });
    um.GetTextUI("Menu")->setCharacterSize(225);
    um.SetTextUI("1 player", "1p");
    um.GetTextUI("1p")->setPosition({ size.x * 0.5f, size.y * 0.5f });
    um.SetTextUI("2 players", "2p");
    um.GetTextUI("2p")->setPosition({ size.x * 0.5f, size.y * 0.75f });
    um.SetTextUI("->", "arrow");
    um.GetTextUI("arrow")->setPosition({ size.x * 0.45f, size.y * 0.5f });
    //Character Select
    um.SetTextUI("1P", "1pArrow", 100, Color::Red);
    um.GetTextUI("1pArrow")->setPosition({ size.x * 0.25f, size.y * 0.5f });
    um.SetTextUI("2P", "2pArrow", 100, Color::Green);
    um.GetTextUI("2pArrow")->setPosition({ size.x * 0.5f, size.y * 0.5f });
    //EndGame
    um.SetTextUI("Game Over", "end", 150, Color::Yellow);
    um.GetTextUI("end")->setPosition({ 700, 400 });

    //instance
    Clock clock;
    //SceneManager sm;
    while ( window.isOpen() )
    {
        //game 분기
        bool Title = true;
        bool SelectMenu = false;
        bool SelectCharacter = false;
        bool PlayGame = false;
        bool GameOver = false;

        int gamemode = 1;
        int onePcharcter = 0;
        int twoPcharcter = 0;
        bool onePlayready = false;
        bool twoPlayready = false;
        int ready = 0;
        Time dt = clock.restart();
        Event ev;
        list<SpriteGameObject*> gameObjectList;
        gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));

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
            else if ( gamemode == 2 )
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
            //charcter Menu
            list<SpriteGameObject*> charcterList;
            charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_green.png"), Vector2f(200, 400)));
            charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_red.png"), Vector2f(800, 400)));
            charcterList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/player_yellow.png"), Vector2f(1400, 400)));
            for ( auto i : charcterList )
            {
                i->setScale(2, 2);
            }
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
                    onePlayready = false;
                    twoPlayready = false;
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
            else if ( gamemode == 2 )
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

            if ( InputManager::GetKeyDown(Keyboard::Return) )
            {
                ready += 1;
                onePlayready = true;


            }
            if ( InputManager::GetKeyDown(Keyboard::Space) && gamemode == 2 )
            {
                ready += 1;
                twoPlayready = true;
            }
            if ( gamemode == 1 && onePlayready )
            {
                SelectCharacter = false;
                PlayGame = true;
            }
            else if ( gamemode == 2 && onePlayready && twoPlayready )
            {
                SelectCharacter = false;
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
        if ( PlayGame && (gamemode == 1 || gamemode == 2) )
        {
            Vector2f timerBarSize(400, 80);
            float duration = 4.0f;
            float timer = duration;
            um.SetRectangleUI("timer Bar", timerBarSize, Color::Red);
            um.GetRectangleUI("timer Bar")->setPosition(
                um.GetwSize().x * 0.5f - timerBarSize.x * 0.5f,
                um.GetwSize().y - 100);
            string charcterIndex[3] = { "graphics/player_green.png","graphics/player_red.png","graphics/player_yellow.png" };
            if ( gamemode == 1 )
            {
                Tree* tree = new Tree(RMI->GetTexture("graphics/tree.png"), gamemode, 1);
                tree->SetPosition({ 960, 900 });
                gameObjectList.push_back(tree);
                Player* player1 = new Player(RMI->GetTexture(charcterIndex[onePcharcter]), gamemode, 1, tree->GetPosition());
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
                Player* player1 = new Player(RMI->GetTexture(charcterIndex[onePcharcter]), gamemode, 1, tree1->GetPosition());
                gameObjectList.push_back(player1);
                Player* player2 = new Player(RMI->GetTexture(charcterIndex[twoPcharcter]), gamemode, 2, tree2->GetPosition());
                gameObjectList.push_back(player2);
            }
            for ( auto i : gameObjectList )
            {
                i->Init();
            }
            while ( PlayGame )
            {
                Time dt = clock.restart(); //?�전 ?�데?�트 ?�간�??�재 ?�데?�트 ?�간 차이 기록
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
                    break;
                }

                float deltaTime = dt.asSeconds();

                for ( auto i : gameObjectList )
                {
                    i->Update(deltaTime);
                }

                window.clear();
                for ( auto i : gameObjectList )
                {
                    i->Draw(window);
                }

                // UI update
                timer -= deltaTime;
                if ( timer < 0.f )
                {
                    timer = 0.f;
                }
                if ( timer == 0.f )
                {
                    ready = 0;
                    gamemode = 1;
                    SelectMenu = false;
                    SelectCharacter = false;
                    PlayGame = false;
                    Title = false;
                    GameOver = true;
                    gamemode = 0;
                    window.clear();
                    break;
                }

                float normTime = timer / duration; // ?�규??
                float timerSizeX = timerBarSize.x * normTime;
                um.GetRectangleUI("timer Bar")->setSize({ timerSizeX, timerBarSize.y });
                um.GetRectangleUI("timer Bar")->setPosition(
                    um.GetwSize().x * 0.5f - timerSizeX * 0.5f,
                    um.GetwSize().y - 100);


                window.draw(*um.GetRectangleUI("timer Bar"));
                window.display();
            }

        }

        //Game over
        while ( GameOver )
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
                Title = true;
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
            window.draw(*(um.GetTextUI("end")));

            window.display();
        }

        for ( auto go : gameObjectList )
        {
            go->Release();
            delete go;
        }
        gameObjectList.clear();


    }

    return 0;
}