//#include "Player2.h"
//#include "InputManager.h"
//
//Player2::Player2(Texture& player)
//	: SpriteGameObject(player), texPlayer(player), originalPos(2),
//	isChop(false), isAlive(true), pos(Sides::Right), score(0)
//{
//	spriteAxe.setTexture(RMI->GetTexture("graphics/axe.png"));
//	Utils::SetOrigin(spriteAxe, Origins::MR);
//
//	for (int i = 0; i < 100; i++)
//	{
//		auto log = new EffectLog(RMI->GetTexture("graphics/log.png"), 5.f);
//		unuseLogs.push_back(log);
//	}
//	chopSound.setBuffer(RMI->GetSoundBuffer("sound/chop.wav"));
//	deathSound.setBuffer(RMI->GetSoundBuffer("sound/death.wav"));
//	chopSound.setVolume(100);
//	deathSound.setVolume(50);
//}
//
//void Player2::Set(Vector2f center)
//{
//	centerPos = center;
//}
//
//void Player2::Clear()
//{
//	auto it = useLogs.begin();
//	while (it != useLogs.end())
//	{
//		unuseLogs.push_back(*it);
//		it = useLogs.erase(it);
//	}
//}
//
//void Player2::Init()
//{
//	sprite.setTexture(texPlayer, true);
//	SetOrigin(Origins::BC);
//	isChop = false;
//	isAlive = true;
//	score = 0;
//
//	Vector2f size = GetSize();
//	axePos.x = -size.x * 0.5f + 70;
//	axePos.y = -size.y * 0.5f + 30;
//
//	originalPos[(int)Sides::Left].x = centerPos.x - size.x * 2;
//	originalPos[(int)Sides::Left].y = centerPos.y;
//
//	originalPos[(int)Sides::Right].x = centerPos.x + size.x * 2;
//	originalPos[(int)Sides::Right].y = centerPos.y;
//
//	SetFlipX(pos == Sides::Left);
//	SetPosition(originalPos[(int)pos]);
//}
//
//void Player2::Release()
//{
//	for (auto i : unuseLogs)
//		delete i;
//	for (auto i : useLogs)
//		delete i;
//	unuseLogs.clear();
//	useLogs.clear();
//}
//
//void Player2::Update(float dt)
//{
//	SpriteGameObject::Update(dt);
//
//	auto it = useLogs.begin();
//	while (it != useLogs.end())
//	{
//		(*it)->Update(dt);
//		if (!(*it)->GetActive())
//		{
//			unuseLogs.push_back(*it);
//			it = useLogs.erase(it);
//		}
//		else
//			it++;
//	}
//
//	if (!isAlive)
//		return;
//
//	if (!isChop)
//	{
//		if (InputManager::GetKeyDown(Keyboard::Left))
//		{
//			Chop(Sides::Left);
//		}
//		if (InputManager::GetKeyDown(Keyboard::Right))
//		{
//			Chop(Sides::Right);
//		}
//	}
//	else
//	{
//		if (pos == Sides::Left && InputManager::GetKeyUp(Keyboard::Left))
//		{
//			isChop = false;
//		}
//		if (pos == Sides::Right && InputManager::GetKeyUp(Keyboard::Right))
//		{
//			isChop = false;
//		}
//	}
//}
//
//void Player2::Draw(RenderWindow& window)
//{
//	SpriteGameObject::Draw(window);
//	if (isChop)
//		window.draw(spriteAxe);
//	
//	for (auto log : useLogs)
//	{
//		log->Draw(window);
//	}
//}
//
//void Player2::SetPosition(Vector2f pos)
//{
//	SpriteGameObject::SetPosition(pos);
//	Vector2f axePos2 = axePos;
//	if (spriteAxe.getScale().x < 0)
//	{
//		axePos2.x *= -1;
//	}
//	spriteAxe.setPosition(pos + axePos);
//}
//
//void Player2::ShowLogEffect()
//{
//	if (unuseLogs.empty())
//		return;
//
//	auto log = unuseLogs.front();
//	unuseLogs.pop_front();
//	useLogs.push_back(log);
//
//	Vector2f force;
//	int forceRanX = Utils::Range(300, 800);
//	// ÁÂ¿ì·Î ³¯¾Æ°¡´Â Èû
//	force.x = pos == Sides::Left ? forceRanX : -forceRanX;
//	// À§·Î ¿Ã¶ó°¡´Â Èû
//	force.y = -800;
//	float aForceRan = Utils::Range(360, 1800);
//	float aForce = pos == Sides::Left ? aForceRan : -aForceRan;
//
//	Vector2f pos = centerPos;
//	pos.y = spriteAxe.getPosition().y;
//
//	log->SetPosition(pos);
//	log->SetOrigin(Origins::MC);
//	log->Fire(force, aForce);
//}
//
//
//bool Player2::GetAlive() const
//{
//	return isAlive;
//}
//
//Sides Player2::GetPos() const
//{
//	return pos;
//}
//
//void Player2::IncreaseScore()
//{
//	score++;
//}
//
//int Player2::GetScore() const
//{
//	return score;
//}
//
//void Player2::Chop(Sides side)
//{
//	chopSound.play();
//	isChop = true;
//	pos = side;
//	SetFlipX(pos == Sides::Left);
//	SetPosition(originalPos[(int)pos]);
//	IncreaseScore();
//	ShowLogEffect();
//}
//
//void Player2::SetFlipX(bool flip)
//{
//	SpriteGameObject::SetFlipX(flip);
//
//	Vector2f scale = spriteAxe.getScale();
//
//	scale.x = flip ? -abs(scale.x) : abs(scale.x);
//	spriteAxe.setScale(scale);
//}
//
//void Player2::Die()
//{
//	deathSound.play();
//	isAlive = false;
//	isChop = false;
//	sprite.setTexture(RMI->GetTexture("graphics/rip.png"), true);
//	Utils::SetOrigin(sprite, Origins::BC);
//	SetFlipX(isAlive);
//}