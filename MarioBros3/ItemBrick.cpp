#include "ItemBrick.h"
#include "Game.h"


ItemBrick::ItemBrick()
{

	tempx = 0;
	tempy = 0;
	typeobject = TypeObject::block;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	isBounce = FALSE;
	isActive = TRUE;
	vx = 0;
	vy = 0;
}

void ItemBrick::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();

	animations->Add(ANI_ACTIVE, ani_set->Get("ani-brick"));
	animations->Add(ANI_EMPTY, ani_set->Get("ani-empty-block"));

}
