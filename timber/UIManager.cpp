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
	SetTextUI("Press Enter to start!", "press enter");
	GetTextUI("press enter")->setPosition({ 500, 600 });
	SetTextUI("Timber!", "title", 150, Color::Yellow);
	GetTextUI("title")->setPosition({ 700, 400 });
	//Menu
	SetTextUI("Menu");
	GetTextUI("Menu")->setPosition({
		wSize.x * 0.5f, wSize.y * 0.5f });
	GetTextUI("Menu")->setPosition({ wSize.x * 0.35f, wSize.y * 0.15f });
	GetTextUI("Menu")->setCharacterSize(225);
	SetTextUI("1 player", "1p");
	GetTextUI("1p")->setPosition({ wSize.x * 0.5f, wSize.y * 0.5f });
	SetTextUI("2 players", "2p");
	GetTextUI("2p")->setPosition({ wSize.x * 0.5f, wSize.y * 0.75f });
	SetTextUI("->", "arrow");
	GetTextUI("arrow")->setPosition({ wSize.x * 0.45f, wSize.y * 0.5f });
	//Character Select
	SetTextUI("1P", "1pArrow", 100, Color::Red);
	GetTextUI("1pArrow")->setPosition({ wSize.x * 0.25f, wSize.y * 0.5f });
	SetTextUI("2P", "2pArrow", 100, Color::Green);
	GetTextUI("2pArrow")->setPosition({ wSize.x * 0.5f, wSize.y * 0.5f });
	//EndGame
	SetTextUI("Game Over", "end", 150, Color::Yellow);
	GetTextUI("end")->setPosition({ 700, 400 });
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