#pragma once
#include "GameObject.h"
#include "Sprites.h"

#define BRICK_BBOX_WIDTH  48
#define BRICK_BBOX_HEIGHT 48
#define TIME_SWITCH 10000
#

#define STATE_BRICK 100
#define STATE_COIN 200

class Brick : 
	public CGameObject
{
	int timeSwitch;
	bool isSwitch;

	CSprite* sprite;
public:
	Brick(float l, float t);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	void Explosion();
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};