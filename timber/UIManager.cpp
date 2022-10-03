#include "UIManager.h"

UIManager::UIManager(Font& _font, Vector2u windowSize)
	: font(_font), wSize(windowSize)
{
}

UIManager::~UIManager()
{
}

void UIManager::Init()
{
	//Title
	SetTextUI("T i m b e r !", "title", 250, Color::Green);
	GetTextUI("title")->setPosition({
		wSize.x * 0.1f, wSize.y * 0.15f });
	SetTextUI("Press Enter to start!", "press enter", 75, Color::Yellow);
	GetTextUI("press enter")->setPosition({
		wSize.x * 0.25f, wSize.y * 0.45f });
	SetTextUI("Team SHY", "team name", 150, Color::Black);
	GetTextUI("team name")->setPosition({
		wSize.x * 0.32f, wSize.y * 0.65f });

	//Menu
	SetTextUI("Game Mode", "Game Mode", 225, Color::Green);
	GetTextUI("Game Mode")->setPosition({
		wSize.x * 0.2f, wSize.y * 0.1f });
	SetTextUI("Single player", "1p");
	GetTextUI("1p")->setPosition({ wSize.x * 0.4f, wSize.y * 0.5f });
	SetTextUI("Local 2 player", "2p");
	GetTextUI("2p")->setPosition({ wSize.x * 0.4f, wSize.y * 0.65f });
	SetTextUI("->", "arrow", 75, Color::Green);

	//Character Select
	SetTextUI("Select", "Select", 150, Color::Green);
	GetTextUI("Select")->setPosition({
		wSize.x * 0.35f, wSize.y * 0.1f });
	SetTextUI("1P", "1pArrow", 100, Color::Red);
	SetTextUI("2P", "2pArrow", 100, Color::Green);
	SetTextUI("Ready", "1pReady", 100, Color::Red);
	SetTextUI("Ready", "2pReady", 100, Color::Green);

	//GamePlay
    Vector2f timerBarSize(400, 80);
	SetRectangleUI("timer Bar", timerBarSize, Color::Red);
	GetRectangleUI("timer Bar")->setPosition(
		wSize.x * 0.5f - timerBarSize.x * 0.5f,
		wSize.y - 100);
	SetTextUI("timer Text");
	GetTextUI("timer Text")->setPosition(wSize.x * 0.45f, wSize.y - 100);
	SetTextUI("0", "1pScore", 100, Color::Magenta);
	GetTextUI("1pScore")->setPosition({ 0, 0 });
	SetTextUI("0", "2pScore", 100, Color::Cyan);
	GetTextUI("2pScore")->setPosition({ wSize.x * 0.5f, 0 });

	//EndGame
	SetTextUI("Game Over!", "end", 150, Color::Yellow);
	GetTextUI("end")->setPosition({ wSize.x * 0.3f,  wSize.x * 0.2f });
}

void UIManager::Release()
{
	for (auto i : textMap)
		delete i.second;
	textMap.clear();

	for (auto i : rectangleMap)
		delete i.second;
	rectangleMap.clear();
}

void UIManager::SetTextUI(
	string textString,
	string name,
	int charSize,
	Color textColor)
{
	Text* text;
	if (name.size() == 0)
		name = textString;
	bool exist = (text = GetTextUI(name)) != nullptr;
	if (!exist)
		text = new Text();
	text->setFont(font);
	text->setString(textString);
	text->setCharacterSize(charSize);
	text->setFillColor(textColor);
	
	if (!exist)
		textMap.insert({ name, text });
}

Text* UIManager::GetTextUI(string name) const
{
	if (textMap.find(name) == textMap.end())
		return nullptr;
	return textMap.find(name)->second;
}

void UIManager::SetRectangleUI(
	string name,
	Vector2f size,
	Color shapeColor)
{
	RectangleShape* shape;
	
	shape = new RectangleShape(size);
	shape->setFillColor(shapeColor);
	rectangleMap.insert({ name, shape });
}

void UIManager::SetRectangleUI(
	string name,
	float sizeX, float sizeY,
	Color shapeColor)
{
	SetRectangleUI(name, Vector2f(sizeX, sizeY), shapeColor);
}

RectangleShape* UIManager::GetRectangleUI(string name) const
{
	if (rectangleMap.find(name) == rectangleMap.end())
		return nullptr;
	return rectangleMap.find(name)->second;
}

Vector2u UIManager::GetwSize() const
{
	return wSize;
}