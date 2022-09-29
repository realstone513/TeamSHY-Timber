#include "ResourceManager.h"
#include "rapidcsv.h"
#include <vector>

string ResourceManager::Filepath = "Resources.csv";

ResourceManager::ResourceManager()
{
	LoadAll();
}

ResourceManager::~ResourceManager()
{
	ReleaseAll();
}

void ResourceManager::ReleaseAll()
{
	for (auto i : texMap)
		delete i.second;
	for (auto i : fontMap)
		delete i.second;
	for (auto i : soundMap)
		delete i.second;
	texMap.clear();
	fontMap.clear();
	soundMap.clear();
}

bool ResourceManager::LoadAll()
{
	ReleaseAll();

	rapidcsv::Document doc(Filepath, rapidcsv::LabelParams(0, -1));

	vector<string> keys = doc.GetColumn<string>(0);
	vector<int> types = doc.GetColumn<int>(1);

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (!Load((ResourceTypes)types[i], keys[i]))
			return false;
	}
	return true;
}

bool ResourceManager::Load(ResourceTypes type, string id)
{
	switch (type)
	{
	case ResourceTypes::Texture:
		return LoadTexture(id);
	case ResourceTypes::Font:
		return LoadFont(id);
	case ResourceTypes::SoundBuffer:
		return LoadSoundBuffer(id);
	}
	return false;
}

bool ResourceManager::LoadTexture(string id)
{
	if (texMap.find(id) != texMap.end())
		return false;

	auto texture = new Texture();
	if (!texture->loadFromFile(id))
	{
		delete texture;
		return false;
	}
	texMap.insert({ id, texture });
	return true;
}

bool ResourceManager::LoadFont(string id)
{
	if (fontMap.find(id) != fontMap.end())
		return false;

	auto font = new Font();
	if (!font->loadFromFile(id))
	{
		delete font;
		return false;
	}
	fontMap.insert({ id, font });
	return true;
}

bool ResourceManager::LoadSoundBuffer(string id)
{
	if (soundMap.find(id) != soundMap.end())
		return false;

	auto soundbf = new SoundBuffer();
	if (!soundbf->loadFromFile(id))
	{
		delete soundbf;
		return false;
	}
	soundMap.insert({ id, soundbf });
	return true;
}

Texture* ResourceManager::GetTexture(string id)
{
	auto texture = texMap.find(id);
	return (texture != texMap.end()) ? texture->second : nullptr;
}

Font* ResourceManager::GetFont(string id)
{
	auto font = fontMap.find(id);
	return (font != fontMap.end()) ? font->second : nullptr;
}

SoundBuffer* ResourceManager::GetSoundBuffer(string id)
{
	auto soundbf = soundMap.find(id);
	return (soundbf != soundMap.end()) ? soundbf->second : nullptr;
}