#pragma once
#include "Mushroom.h"
class UPMushroom :
    public Mushroom
{
public:
	UPMushroom();
	virtual void Pre_Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

