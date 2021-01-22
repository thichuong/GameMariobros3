#pragma once
#include "GameObject.h"

#define BoomerangBrother_STATE_WALKING 100
#define BoomerangBrother_STATE_DIE 200
#define BoomerangBrother_STATE_ATTACK 300
#define BoomerangBrother_BBOX_WIDTH 48.0f
#define BoomerangBrother_BBOX_HEIGHT 72.0f
#define BoomerangBrother_GRAVITY  0.003f
#define BoomerangBrother_WALKING_SPEED 0.05f
#define BoomerangBrother_TIME_CHANGE_VX 1500
#define BoomerangBrother_TIME_ATTACK 2500
#define BoomerangBrother_FLY_DIE 0.9f

class BoomerangBrother :
    public CGameObject
{
public:
    ULONGLONG timeattack;
	ULONGLONG timechangeVX;

	BoomerangBrother();

	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Render();
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
};

