#pragma once
#include "GameObject.h"
#define BBOX_WIDTH  48
#define BBOX_HEIGHT 48

class CCollisionBox :
    public CGameObject
{
	float box_width, box_height;
public:
	CCollisionBox(float l, float t, float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
};

