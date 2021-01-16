#pragma once
#include "Plant.h"

#define PIRANHA_WIDTH 48
#define PIRANHA_HEIGHT 92

#define ANI_PIRANHA "ani-red-piranha-plant-attack"
class Piranha :
    public Plant
{
public:
    Piranha();

   
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void DelObject();
};

