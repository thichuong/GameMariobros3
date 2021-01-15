#pragma once
#include "GameObject.h"
#include "Resource.h"
#include "Game.h"

#define ANI_FX "FX"

class FXObject :
    public CGameObject
{
protected:
    DWORD time_FX;
    int time_explosion;
public:
    FXObject();
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Explosion();
    virtual void Render();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0, t = 0, r = 0, b = 0; }
};

