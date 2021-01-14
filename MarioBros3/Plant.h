#pragma once
#include "GameObject.h"

#define TIME_HIDE  2500;
#define TIME_IDLE  800;
#define PLANT_SPEED 0.14f;
#define PLANT_ANI 

enum class PlantState
{
	slideup,
	slidedown,
	idle,
	hide
};

class Plant :
    public CGameObject
{
protected:

    int idleTime, hideTime;
    int maxHeight;
	int tempHeight;
	PlantState plantstate;
	int with;
	int height;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	Plant();
	virtual void SetState(PlantState state);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
};

