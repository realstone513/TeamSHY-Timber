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