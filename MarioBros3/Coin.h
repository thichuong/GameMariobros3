#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH		42
#define COIN_BBOX_HEIGHT	48
#define COIN_BBOX_FLY	0.06f
#define COIN_BBOX_FLY_TIME	250


class Coin :
    public CGameObject
{
	bool Fly;
	int time;
public:
	Coin(float l, float t, bool Fly = FALSE);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

