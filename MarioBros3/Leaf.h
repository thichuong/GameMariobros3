#pragma once
#include "GameObject.h"

#define LEAF_BBOX_WIDTH		42
#define LEAF_BBOX_HEIGHT	48
#define TIME 800
#define LFY_X 0.08f
#define LFY_Y 0.06f
#define	LFY_Y_NEW 0.6f
class Leaf :
    public CGameObject
{
	DWORD time;
public:
	Leaf(float l, float t, bool Fly = FALSE);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

