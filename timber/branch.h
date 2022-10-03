#pragma once
#include "SpriteGameObject.h"

class Branch : public SpriteGameObject
{
private:
    Sides side;

public:
    Branch(Texture& tex);
    virtual void Init() override;
    void SetSide(Sides side, int gamemode);
    Sides GetSide();
};

