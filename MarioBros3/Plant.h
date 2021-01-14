#pragma once
#include "GameObject.h"

#define TIME_HIDE  3000
#define TIME_IDLE  800
#define TIME_GROW	200
#define PLANT_SPEED 0.14f
#define TIME_LIFE 500
#define DIE_ANI "ani-mario-damaged"

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

    int idleTime, hideTime, growTime;
	int timeLive;
    int maxHeight;
	int tempHeight;
	PlantState plantstate;
	int with;
	int height;
	bool live;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	Plant();
	void setPlant();
	virtual void SetState(PlantState state);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
	virtual void DelObject() =0;
};

