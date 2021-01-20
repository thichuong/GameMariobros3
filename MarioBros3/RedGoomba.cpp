#include "RedGoomba.h"


RedGoomba::RedGoomba()
{
	SetState(GOOMBA_STATE_FLY);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	flydie = false;
	timedie = 0;
	SetAnimationSet(CAnimations::GetInstance());
}

void RedGoomba::Render()
{
	D3DXVECTOR2 pScale(1, 1);
	string ani = GOOMBA_RED_ANI_WALKING;

	if (state == GOOMBA_STATE_DIE) {
		if (!flydie)
			ani = GOOMBA_RED_ANI_DIE;
		else
		{
			ani = GOOMBA_RED_ANI_IDLE;
			pScale.y = -pScale.y;
		}
	}
	if (state == GOOMBA_STATE_FLY)
	{
		ani = GOOMBA_RED_ANI_FLY;
	}
	
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, pScale);
	//animations->Get(ani)->Render(x, y);

}