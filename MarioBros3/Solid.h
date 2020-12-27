#pragma once
#include "GameObject.h"

class Solid :
	public CGameObject
{
	float box_width, box_height;
public:
	Solid(float l, float t, float w, float h);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
};

