#include "Branch.h"
#include "ResourceManager.h"

Branch::Branch(Texture& tex)
	: SpriteGameObject(tex)
{

}

void Branch::Init()
{
    Utils::SetOrigin(sprite, Origins::MC);
}

void Branch::SetSide(Sides side,int gamemode)
{
    if (gamemode == 1)
    {
        switch (side)
        {
        case Sides::Left:
            sprite.setTexture(PRMI->GetTexture("graphics/1P_log(b)_L.png"));
            this->side = Sides::Left;
            break;
        case Sides::Right:
            sprite.setTexture(PRMI->GetTexture("graphics/1P_log(b)_R.png"));
            this->side = Sides::Right;
            break;
        case Sides::None:
            sprite.setTexture(PRMI->GetTexture("graphics/1P_log(b)_N.png"));
            this->side = Sides::None;
            break;
        }
    }
    else
    {
        switch (side)
        {
        case Sides::Left:
            sprite.setTexture(PRMI->GetTexture("graphics/2P_log(b)_L.png"));
            this->side = Sides::Left;
            break;
        case Sides::Right:
            sprite.setTexture(PRMI->GetTexture("graphics/2P_log(b)_R.png"));
            this->side = Sides::Right;
            break;
        case Sides::None:
            sprite.setTexture(PRMI->GetTexture("graphics/2P_log(b)_N.png"));
            this->side = Sides::None;
            break;
        }
    }

}

Sides Branch::GetSide()
{
    return side;
}