#pragma once
#include "GameObject.h"

#define Bullet_BBOX_WIDTH  24
#define Bullet_BBOX_HEIGHT 24
#define Bullet_SPEED 0.6
#define GRAVITY  0.003f
#define Bullet_JUMP 0.0f

#define ANI "ANI"
class CFireBullet :
    public CGameObject
{
public:
	CFireBullet(float x, float y, int ax);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

