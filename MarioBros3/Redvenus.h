#pragma once
#include "Plant.h"
#include "FireBall.h"

#define VENUS_WIDTH 48
#define VENUS_HEIGHT 92

#define HeadUp "ani-red-venus-fire-trap-headup"
#define HeadDown "ani-red-venus-fire-trap-headdown"

#define IdleHeadUp "ani-red-venus-fire-trap-headup-idle"
#define IdleHeadDown "ani-red-venus-fire-trap-headdown-idle"

#define fireBallLocation 24

class Redvenus :
    public Plant
{
   D3DXVECTOR2 HeadVenus;
   FireBall* fireBalls;
   bool canShot;
public:
    Redvenus();
   
    void addFireBall(float fireBallvy);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void DelObject();
};

