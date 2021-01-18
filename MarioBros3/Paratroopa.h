#pragma once
#include "GameObject.h"
#include "Koopas.h"

#define TROOPA_LFY 0.9f
#define KOOPAS_ANI_TROOPA "ani-green-koopa-paratroopa-fly"
#define KOOPAS_ANI_Y 8

class Paratroopa :
    public CGameObject
{
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	Paratroopa();
	virtual void SetState(int state);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);

	void swicth(int state ,float vx);
};

