#pragma once
#include "GameObject.h"
#include "Resource.h"


class WarpPipe :
    public CGameObject
{
protected:
    TypeWarp typewarp;
    float box_width, box_height;
public:
    WarpPipe(float l, float t, float w, float h);
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
    void setWarp(TypeWarp type) { typewarp = type; }
};

