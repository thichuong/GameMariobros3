#pragma once
#include "FXObject.h"


#define ANI_MARIO_DAMAGE "ani-mario-damaged" 
#define TIME_MARIO_DAMAGE 500

class MarioDamageFX : public FXObject
{
public:
    MarioDamageFX();
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Explosion();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0, t = 0, r = 0, b = 0; }
};

