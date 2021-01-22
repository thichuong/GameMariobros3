#include "PSwitch.h"
#include "Game.h"
#include "Coin.h"
#include "Brick.h"
PSwitch::PSwitch(float l, float t) :CGameObject()
{
	x = l ;
	y = t - PSWITCH_BBOX_HEIGHT;
	typeobject = TypeObject::normal;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	isActive = true;
	Bounce = false;
}
void PSwitch::Render()
{
	string ani = ANI_DEFAULT;
	if (!isActive) ani = ANI_PRESSED;
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y );
	RenderBoundingBox();
}

void PSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y ;
	r = x + PSWITCH_BBOX_WIDTH;
	if (isActive)
		b = y + PSWITCH_BBOX_HEIGHT;
	else
		b = y + PSWITCH_BBOX_PRESSED_HEIGHT;
}
void PSwitch::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();

	animations->Add(ANI_DEFAULT, ani_set->Get("ani-switch-block-blue-active"));
	animations->Add(ANI_PRESSED, ani_set->Get("ani-switch-block-blue-inactive"));
}
void PSwitch::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player && isActive && ny < 0)
	{
		Bounce = true;
		y += PSWITCH_BBOX_HEIGHT - PSWITCH_BBOX_PRESSED_HEIGHT;
		isActive = false;
	}
}
void PSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (Bounce )
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = coObjects->at(i);
			if (obj->typeobject == TypeObject::brick)
			{
				if (obj->GetState() == STATE_BRICK)	obj->SetState(STATE_COIN);
				else if(obj->GetState() == STATE_COIN) obj->SetState(STATE_BRICK);
				
			}
		}
		Bounce = false;
	}
	

}
