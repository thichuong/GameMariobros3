#pragma once
#include "Plant.h"
#include "FireBall.h"

#define VENUS_WIDTH 48.0f
#define VENUS_HEIGHT 92.0f

#define HeadUp "ani-red-venus-fire-trap-headup"
#define HeadDown "ani-red-venus-fire-trap-headdown"

#define IdleHeadUp "ani-red-venus-fire-trap-headup-idle"
#define IdleHeadDown "ani-red-venus-fire-trap-headdown-idle"

#define fireBallLocation 24

class Redvenus :
    public Plant
{
 protected:
    D3DXVECTOR2 HeadVenus;
   FireBall* fireBalls;
   bool canShot;
public:
    Redvenus();
   
    void addFireBall(float fireBallvy);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Pre_Render();
    virtual void DelObject();
    virtual void SetAnimationSet(CAnimations* ani_set);
};

