#pragma once
#pragma once
#include "GameObject.h"

#define PLATFORM_ANI "ani-platform"
#define PLATFORM_GRAVITTY 0.1f
#define PLATFORM_BOX_WIDTH 144
#define PLATFORM_BOX_HEIGHT 48
#define PLUS 40

class Platform :
	public CGameObject
{

	bool isGravity;
public:
	Platform();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);


};


