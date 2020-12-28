#pragma once
#include "GameObject.h"

#define BOUNCE_VEL	12.0f
#define QuestionBlock_BBOX_WIDTH 48
#define QuestionBlock_BBOX_HEIGHT 48
#define GRAVITY  0.8f

enum class Item
{
	RedShroom,
	RaccoonLeaf,
	FireFlower,
	GreenShroom,
	Coin
};

class QuestionBlock :
    public CGameObject
{
	bool isBounce;
	bool isActive;
	int quantity;
	float tempx, tempy;
	Item item;
public:
	QuestionBlock(float l, float t);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetItem(Item inblockitem) { this->item = inblockitem; }
	void SetQuantity(int quantity);
};

