#include "DebrisFx.h"

#include "Player.h"
DebrisFx::DebrisFx()
{
	time_FX = GetTickCount64();
	SetAnimationSet(CAnimations::GetInstance());
	collision = CCollision::None;
	time_explosion = DEBRIS_TiME;
	DebugOut(L"[ DebrisFx ] \n");
}
void DebrisFx::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI_FX, ani_set->Get("ani-brick-debris"));
}
void DebrisFx::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;
	x += dx;
	if (GetTickCount64() - time_FX > time_explosion)
		this->Explosion();
	if (GetTickCount64() - time_FX > DEBRIS_TiME_FLY)
	{
		vy += dt * DEBRIS_GRAVITY;
	}
	else
	{
		vx = Force.x;
		vy = Force.y;
	}
}
void DebrisFx::Explosion()
{
	
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
	
}