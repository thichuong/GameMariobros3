#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	bool isReward;
	float width;
	float height;
	ULONGLONG time_tick;
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	int GetSceneId() { return scene_id;  }
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};