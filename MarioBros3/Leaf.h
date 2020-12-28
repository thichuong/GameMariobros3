#pragma once
#include "GameObject.h"

#define LEAF_BBOX_WIDTH		42
#define LEAF_BBOX_HEIGHT	48
#define TIME 500
#define LFY_X 0.04
#define LFY_Y 0.06
class Leaf :
    public CGameObject
{
	int time;
public:
	Leaf(float l, float t, bool Fly = FALSE);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

