#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.03f;
#define KOOPAS_RUN_SPEED 0.1f
#define KOOPAS_GRAVITY  0.003f
#define KOOPAS_FLY 0.7f


#define KOOPAS_BBOX_WIDTH 48
#define KOOPAS_BBOX_HEIGHT 78
#define KOOPAS_BBOX_HEIGHT_DIE 48

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_SHELL 300
#define KOOPAS_STATE_SHELL_RUN 400
#define KOOPAS_STATE_SHELL_HOLD 500

#define KOOPAS_ANI_WALKING "ani-green-koopa-troopa-move"
#define KOOPAS_ANI_DIE "ani-green-koopa-troopa-crouch"
#define KOOPAS_ANI_SHELL "ani-green-koopa-troopa-crouch"
#define KOOPAS_ANI_SHELL_RUN "ani-green-koopa-troopa-shell-run"

class CKoopas : public CGameObject
{
public:
	bool FlipY;
public:
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();


	CKoopas();
	virtual void SetState(int state);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
};