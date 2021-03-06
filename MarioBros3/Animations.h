#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Sprites.h"

/*
Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	float defaultTime;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(float defaultTime = 100) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(LPSPRITE sprite, float time = 0);
	void Render(float x, float y, DWORD timeRender, bool flipx = FALSE, int alpha = 255);
	void Render(float x, float y, bool flipx = FALSE, int alpha = 255 );
	void Render(float x, float y,D3DXVECTOR2 vectorflip, int alpha = 255);
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<string, LPANIMATION> animations;

public:
	
	void Add(string id, LPANIMATION ani);
	LPANIMATION Get(string id);
	void Clear();
	

	static CAnimations * GetInstance();
};

typedef vector<LPANIMATION> CAnimationSet;

typedef CAnimationSet* LPANIMATION_SET;

/*
	Manage animation set database
*/
class CAnimationSets
{
	static CAnimationSets * __instance;

	unordered_map<string, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	CAnimationSets(string aniID, DWORD defaultTime = 100);
	void Add(string id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(string id);


	static CAnimationSets * GetInstance();
};