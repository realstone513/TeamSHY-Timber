#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Singleton.h"

// 싱글턴 or 스태틱 사용해서 전역적 사용가능하게
// 파일 이름 목록이 담긴 csv파일 사용해서 파일입력 & 리소스 로드
// 로드 & 릴리즈, Get()

#define PRMI *ResourceManager::GetInstance()
#define RMI ResourceManager::GetInstance()

using namespace std;
using namespace sf;

enum class ResourceTypes
{
	Texture, Font, SoundBuffer,
};

class ResourceManager : public Singleton<ResourceManager>
{
private:
	map<string, Texture*>		texMap;
	map<string, Font*>			fontMap;
	map<string, SoundBuffer*>	soundMap;

	vector<Vector2i>			statusVector;

	static string ResourceFilepath;
	static string StatusFilepath;

public:
	ResourceManager();
	~ResourceManager();
	
	void			ReleaseAll();

	bool			LoadAll();
	bool			Load(ResourceTypes type, string id);
	bool			LoadTexture(string id);
	bool			LoadFont(string id);
	bool			LoadSoundBuffer(string id);

	Texture*		GetTexture(string id);
	Font*			GetFont(string id);
	SoundBuffer*	GetSoundBuffer(string id);

	void			LoadStatus();
	Vector2i		GetStatus(int type);
};