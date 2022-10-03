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

void Branch::SetSide(Sides side)
{
    switch (side)
    {
    case Sides::Left:
        sprite.setTexture(RMI->GetTexture("graphics/1P_log(b)_L.png"));
        this->side = Sides::Left;
        break;
    case Sides::Right:
        sprite.setTexture(RMI->GetTexture("graphics/1P_log(b)_R.png"));
        this->side = Sides::Right;
        break;
    case Sides::None:
        sprite.setTexture(RMI->GetTexture("graphics/1P_log(b)_N.png"));
        this->side = Sides::None;
        break;
    }
}

Sides Branch::GetSide()
{
    return side;
}