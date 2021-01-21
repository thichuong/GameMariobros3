#pragma once
#include "Mario.h"

#define ANI_SMALL_MAP "ani_small"
#define ANI_BIG_MAP "ani_big"
#define ANI_FIRE_MAP "ani_fire"
#define ANI_RACCOON_MAP "ani_raccoon"

#define MARIO_MAP_BBOX_WIDTH  48.0f
#define MARIO_MAP_BBOX_HEIGHT 48.0f

#define MARIO_MAP_RANGE 96.0f
#define MARIO_MAP_SPEED 0.1f

class MapMario :
    public CMario
{
	bool isGoing;
	float range;
	float tempx, tempy;

	bool up, down, left, right;
public:
	string levelMario;

	MapMario();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void KeyState(BYTE* state);
	virtual void OnKeyDown(int keyCode);
};

