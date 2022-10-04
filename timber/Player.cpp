#include "Player.h"
#include "InputManager.h"
#include "Tree.h"

Player::Player(Texture& player, int gamemode, int is1P2P, Vector2f treepos, Texture& axe, int characterType)
    : SpriteGameObject(player), texPlayer(player), gameMode(gamemode), is1P2P(is1P2P), isChop(false), treePos(treepos), originalPos(2), score(0)
{
    texAxe.setTexture(axe);
    Utils::SetOrigin(texAxe, Origins::MR);
    Vector2f size = GetSize();

    axePos.x = -size.x * 0.5f + 70;
    axePos.y = -size.y * 0.5f;
    SetOrigin(Origins::BC);

    score = 0;
    scoreStatus = true;

    if (gameMode == 1)
    {
        addScore = 10;
        minusScore = 10;
    }
    else
    {
        Vector2i temp = RMI->GetStatus(characterType);
        addScore = temp.x;
        minusScore = temp.y;
    }
}

Player::~Player()
{
}

void Player::Init()
{
    sprite.setTexture(texPlayer, true);
    SetOrigin(Origins::BC);
    if (is1P2P == 1)
    {
        SetPosition(Vector2f({ 300, 1000 }));
    }
    else
    {
        SetPosition(Vector2f({ 900, 1000 }));
    }
    isChop = false;

    Vector2f size = GetSize();
    originalPos[(int)Sides::Left].x = treePos.x - size.x * 2;
    originalPos[(int)Sides::Left].y = treePos.y;

    originalPos[(int)Sides::Right].x = treePos.x + size.x * 2;
    originalPos[(int)Sides::Right].y = treePos.y;

    SetFlipX(side == Sides::Left);
    SetPosition(originalPos[(int)side]);
    score = 0;
    scoreStatus = true;

    chopSound.setBuffer(PRMI->GetSoundBuffer("sound/chop.wav"));
    deathSound.setBuffer(PRMI->GetSoundBuffer("sound/death.wav"));
}

void Player::Release()
{
}

void Player::Update(float dt)
{
    SpriteGameObject::Update(dt);
    if (is1P2P == 1)
    {
        if (!isChop)
        {
            if (InputManager::GetKeyDown(Keyboard::A))
            {
                Chop(Sides::Left);
                if ( !scoreStatus )
                {
                    score -= minusScore;
                    scoreStatus = true;
                }
                else
                    score += addScore;
            }
            if (InputManager::GetKeyDown(Keyboard::D))
            {
                Chop(Sides::Right);
                if ( !scoreStatus )
                {
                    score -= minusScore;
                    scoreStatus = true;
                }
                else
                    score += addScore;
            }
        }
        else
        {
            if (side == Sides::Left && InputManager::GetKeyUp(Keyboard::A))
            {
                isChop = false;
            }
            if (side == Sides::Right && InputManager::GetKeyUp(Keyboard::D))
            {
                isChop = false;
            }
        }
    }
    else
    {
        if (!isChop)
        {
            if (InputManager::GetKeyDown(Keyboard::Left))
            {
                Chop(Sides::Left);
                if ( !scoreStatus )
                {
                    score -= minusScore;
                    scoreStatus = true;
                }
                else
                    score += addScore;
            }
            if (InputManager::GetKeyDown(Keyboard::Right))
            {
                Chop(Sides::Right);
                if ( !scoreStatus )
                {
                    score -= minusScore;
                    scoreStatus = true;
                }
                else
                    score += addScore;
            }
        }
        else
        {
            if (side == Sides::Left && InputManager::GetKeyUp(Keyboard::Left))
            {
                isChop = false;
            }
            if (side == Sides::Right && InputManager::GetKeyUp(Keyboard::Right))
            {
                isChop = false;
            }
        }
    }
}

void Player::Draw(RenderWindow& window)
{
    SpriteGameObject::Draw(window);
    if (isChop)
    {
        window.draw(texAxe);
    }
}

void Player::SetPosition(Vector2f pos)
{
    SpriteGameObject::SetPosition(pos);
    Vector2f axePos2 = axePos;
    if ( texAxe.getScale().x < 0 )
    {
        axePos2.x *= -1;
    }
    texAxe.setPosition(pos + axePos);
}

void Player::SetFlipX(bool flip)
{
    SpriteGameObject::SetFlipX(flip);

    Vector2f scale = texAxe.getScale();

    scale.x = flip ? -abs(scale.x) : abs(scale.x);
    texAxe.setScale(scale);
}

void Player::Chop(Sides side)
{
    isChop = true;
    this->side = side;
    SetFlipX(this->side == Sides::Left);
    SetPosition(originalPos[(int)side]);
    chopSound.play();
}

void Player::Die()
{
    if ( !isAlive )
    {
        deathSound.play();
    }
    isAlive = false;
    isChop = true;
    sprite.setTexture(PRMI->GetTexture("graphics/rip.png"), true);
    texAxe.setScale(0, 0);
    SetFlipX(false);
    Utils::SetOrigin(sprite, Origins::BC);
}

Sides Player::GetPlayerSide()
{
    return side;
}

int Player::GetScore()
{
    return score;
}

void Player::SetScoreStatus()
{
    scoreStatus = false;
}