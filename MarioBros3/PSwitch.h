#pragma once
#include "GameObject.h"

#define PSWITCH_BBOX_WIDTH	48
#define PSWITCH_BBOX_HEIGHT	48
#define PSWITCH_BBOX_PRESSED_HEIGHT 21

#define ANI_DEFAULT "ani-switch-block"
#define ANI_PRESSED "ani-switch-block-pressed"

#define PRESSED_Y 

class PSwitch :
    public CGameObject
{
	bool isActive;
	bool Bounce;

public:
	PSwitch(float l, float t);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

