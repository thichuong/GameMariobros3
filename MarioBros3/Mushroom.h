#pragma once
#include "GameObject.h"

#define Mushroom_BBOX_WIDTH		42
#define Mushroom_BBOX_HEIGHT	48
#define Mushroom_VX_X 0.08f
#define Mushroom_VX_Y 0.3f
#define Mushroom_GRAVITY  0.003f

class Mushroom :
    public CGameObject
{
public:
	Mushroom();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Pre_Render();
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	
};

