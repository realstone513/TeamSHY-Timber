#include "SceneManager.h"


SceneManager::SceneManager()
{
    Title = true;
    SelectMenu = false;
    SelectCharacter = false;
    PlayGame = false;
    GameOver = false;

    gamemode = 1;
    onePcharcter = 0;
    twoPcharcter = 0;
    onePlayready = false;
    twoPlayready = false;
    ready = 0;

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "timber", Style::Default);
    gameObjectList.push_back(new SpriteGameObject(RMI->GetTexture("graphics/background.png")));
}

void titleScene()
{
    //while ( Title )
    //{
    //    Time dt = clock.restart();
    //    Event ev;
    //    InputManager::ClearInput();

    //    while ( window.pollEvent(ev) )
    //    {
    //        InputManager::UpdateInput(ev);
    //    }

    //    if ( InputManager::GetKeyDown(Keyboard::Key::Return) )
    //    {
    //        SelectMenu = true;
    //        Title = false;
    //        break;
    //    }
    //    if ( InputManager::GetKeyDown(Keyboard::Key::Escape) )
    //    {
    //        window.close();
    //        break;
    //    }

    //    float deltaTime = dt.asSeconds();

    //    //Update
    //    for ( auto go : gameObjectList )
    //    {
    //        go->Update(deltaTime);
    //    }

    //    //Draw
    //    window.clear();
    //    for ( auto go : gameObjectList )
    //    {
    //        go->Draw(window);
    //    }
    //    window.draw(*(um.GetTextUI("title")));
    //    window.draw(*(um.GetTextUI("press enter")));

    //    window.display();
    //}
    
}
