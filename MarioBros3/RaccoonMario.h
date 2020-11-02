#pragma once
#include "Mario.h"

#define RACCOONMARIO_TIMECOOLDOWN 300
#define RACCOONMARIO_ANI_ATTACKTIME 200
#define RACCOONMARIO_ATTACKTIME		50

class RaccoonMario :
    public CMario
{

public:
	RaccoonMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetAnimationSet(CAnimations* ani_set);
	void TailAttack(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
};

