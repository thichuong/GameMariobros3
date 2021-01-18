#pragma once
#include "Plant.h"

#define PIRANHA_WIDTH 48
#define PIRANHA_HEIGHT 70

#define ANI_PIRANHA "ani-red-piranha-plant-attack"
class Piranha :
    public Plant
{
public:
    Piranha();

   
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Pre_Render();
    virtual void DelObject();
};

