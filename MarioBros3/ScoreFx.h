#pragma once
#include "FXObject.h"

#define SCORE_FX_TIME	500

#define SCORE_FX_FLY	0.2f



class ScoreFx :
    public FXObject
{
    int levelScore;
public:
    ScoreFx(int level);
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    virtual void Explosion();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b) { l = 0, t = 0, r = 0, b = 0; }
};

