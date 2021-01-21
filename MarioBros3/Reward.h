#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "ItemCard.h"

#define SWITCH_TIME 200
#define REWARD_BBOX_X 48
#define REWARD_BBOX_Y 48


class Reward :
    public CGameObject
{
  
	CSprite* items[3];
	float time_switch;
	int reward;

	
public:
	Reward(float l, float t);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

