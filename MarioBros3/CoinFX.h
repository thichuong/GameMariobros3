#pragma once
#include "FXObject.h"

#define COIN_FX_TIME	1000
#define COIN_FX_FLY_TIME     350
#define COIN_FX_FLY	0.4f
#define COIN_GRAVITY 0.002f;
class CoinFX :
    public FXObject
{
public:
    CoinFX();
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Explosion();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0, t = 0, r = 0, b = 0; }
};

