#pragma once
#include "GameObject.h"

#define PLATFORM_ANI "ani-platform"
#define PLATFORM_GRAVITTY 0.3f

class Platform :
    public CGameObject
{
    float width, height;
	bool isGravity;
public:
	Platform();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void setWidthHeight(float w, float h) { width = w; height = h; }
	
};

