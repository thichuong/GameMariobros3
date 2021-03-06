#pragma once
#include "FXObject.h"

#define ANI_SMOKE "ani-fireball-damaged"
#define TIME_SMOKE 400

class SmokeFx :
    public FXObject
{
public:
    SmokeFx();
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Explosion();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0, t = 0, r = 0, b = 0; }
};

