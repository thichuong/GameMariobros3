#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f;
#define GOOMBA_GRAVITY  0.003f
#define GOOMBA_FLY_DIE 0.9f

#define GOOMA_TIME_DIE 200

#define GOOMBA_BBOX_WIDTH 48
#define GOOMBA_BBOX_HEIGHT 48
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define GOOMBA_ANI_WALKING "ani-goomba-walk"
#define GOOMBA_ANI_DIE "ani-goomba-die"
#define GOOMBE_ANI_IDLE	"ani-goomba-idle"

class CGoomba : public CGameObject
{
	bool flydie;
	DWORD timedie;
public:
	CGoomba();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Render();
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
};