#pragma once
#include "GameObject.h"

#define Tail_BBOX_WIDTH  120
#define Tail_BBOX_HEIGHT 12

class MarioTail :
    public CGameObject
{
public:
	MarioTail(float x, float y);
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set) {};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

