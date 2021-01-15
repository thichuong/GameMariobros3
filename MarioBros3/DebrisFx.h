#pragma once
#include "FXObject.h"

#define DEBRIS_TiME 500
#define  DEBRIS_TiME_FLY 50
#define DEBRIS_GRAVITY 0.002f;

class DebrisFx :
    public FXObject
{
    D3DXVECTOR2 Force;
public:
    DebrisFx();
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Explosion();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0, t = 0, r = 0, b = 0; }
    void setForce(float fx, float fy) { Force.x = fx, Force.y = fy; }
};

