#pragma once
#include "GameObject.h"
#define BBOX_WIDTH  48
#define BBOX_HEIGHT 48

class CCollisionBox :
    public CGameObject
{

public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
};

