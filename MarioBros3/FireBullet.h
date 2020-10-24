#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48
class CFireBullet :
    public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
};

