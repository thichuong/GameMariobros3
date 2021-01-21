#pragma once
#include "Paratroopa.h"

#define  KOOPAS_RED_ANI_TROOPA "ani-red-koopa-paratroopa-fly"
#define KOOPAS_RED_RANGE 192.0f
#define KOOPAS_RED_VY 0.2f

class RedParatroopa :
    public Paratroopa
{
	float Range;
	float tempy;
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void swicth(int state, float vx);
	RedParatroopa();
};

