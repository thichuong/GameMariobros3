#pragma once
#include "Mario.h"
#define FLOAT "float"

class RaccoonMario :
    public CMario
{
	bool slowFall;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetAnimationSet(CAnimations* ani_set);
};

