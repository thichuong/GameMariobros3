#pragma once
#include "Plant.h"

#define VENUS_WIDTH 48
#define VENUS_HEIGHT 92

#define HeadUp "ani-red-venus-fire-trap-headup"
#define HeadDown "ani-red-venus-fire-trap-headdown"

#define IdleHeadUp "ani-red-venus-fire-trap-headup-idle"
#define IdleHeadDown "ani-red-venus-fire-trap-headdown-idle"

class Redvenus :
    public Plant
{
    D3DXVECTOR2 HeadVenus;
   // CObjectPool fireBalls;
public:
    Redvenus();
    
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
};

