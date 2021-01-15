#pragma once
#include "FXObject.h"

#define REWARD_TIME 1000
#define REWARD_SPEED 0.4f

class RewardFX :
    public FXObject
{
    int reWard;
public:
    RewardFX(int reWard);
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Explosion();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0, t = 0, r = 0, b = 0; }
};

