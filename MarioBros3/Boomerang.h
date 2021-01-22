#pragma once
#include "GameObject.h"

#define Boomerang_SPEED 0.3f
#define Boomerang_VY 0.1f
#define Boomerang_CHANGE_VY 0.15f
#define TIME_CHANG_VY 800
#define TIME_CHANG_VX 1500


class Boomerang :
    public CGameObject
{
	ULONGLONG time_shot;

public:
	bool active;
	Boomerang(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

