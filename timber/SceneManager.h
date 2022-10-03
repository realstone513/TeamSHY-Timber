#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "SpriteGameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"

using namespace std;
using namespace sf;

class SceneManager
{
private:
    bool Title;
    bool SelectMenu;
    bool SelectCharacter;
    bool PlayGame;
    bool GameOver;

    int gamemode;
    int onePcharcter;
    int twoPcharcter;
    bool onePlayready;
    bool twoPlayready;
    int ready;
    RenderWindow window;
    list<SpriteGameObject*> gameObjectList;
    Clock clock;
public:
    SceneManager();
    ~SceneManager();
    void Init();
    void titleScene();
};

