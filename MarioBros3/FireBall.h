#pragma once
#include "GameObject.h"

#define Bullet_BBOX_WIDTH  24
#define Bullet_BBOX_HEIGHT 24
#define FIRE_SPEED 0.2f
#define ANI "ANI"

class FireBall :
    public CGameObject
{
	bool active;
public:
	bool getactive() { return active; }
	FireBall(float x, float y, int ax, float vy);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

