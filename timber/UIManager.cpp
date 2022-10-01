#include "UIManager.h"
<<<<<<< HEAD

UIManager::UIManager(Font& _font)
	: font(_font)
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

	for (auto i : shapeMap)
		delete i.second;
	shapeMap.clear();
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
=======
>>>>>>> d148df034bed63e75925ac500a78b7377e25d359
