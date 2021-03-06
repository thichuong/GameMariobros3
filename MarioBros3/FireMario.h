#pragma once
#include "Mario.h"
#include "FireBullet.h"

#define FIREMARIO_TIMECOOLDOWN 200
#define FIREMARIO_ANI_ATTACKTIME 200

class FireMario :
    public CMario
{
	
public:
	FireMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetAnimationSet(CAnimations* ani_set);
};

