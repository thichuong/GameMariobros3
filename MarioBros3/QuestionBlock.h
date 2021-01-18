#pragma once
#include "GameObject.h"

#define BOUNCE_VEL	12.0f
#define QuestionBlock_BBOX_WIDTH 48
#define QuestionBlock_BBOX_HEIGHT 48
#define GRAVITY_QUESTIONBLOCK  0.8f

#define ANI_ACTIVE "ani-question-block"
#define ANI_EMPTY "ani-empty-block"

enum class Item
{
	RedShroom,
	Leaf,
	FireFlower,
	GreenShroom,
	Coin,
	PSwitch
};

class QuestionBlock :
    public CGameObject
{
protected:
	bool isBounce;
	bool isActive;
	int quantity;
	float tempx, tempy;
	Item item;
public:
	QuestionBlock(float l, float t);
	QuestionBlock();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void SetItem(Item inblockitem) { this->item = inblockitem; }
	void SetQuantity(int quantity);
	void Bounce();
};

