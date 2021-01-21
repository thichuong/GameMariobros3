#pragma once
#include "GameObject.h"


#define TREE_BBOX_WIDTH 48
#define TREE_BBOX_HEIGHT 48

#define TREE_ANI "ani-tree"
class CTree :
    public CGameObject
{
public:
	CTree();
	virtual void Render();
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

