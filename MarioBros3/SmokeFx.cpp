#include "SmokeFx.h"

SmokeFx::SmokeFx()
{
	time_FX = GetTickCount64();
	collision = CCollision::None;
	time_explosion = TIME_SMOKE;
	SetAnimationSet(CAnimations::GetInstance());
}
void SmokeFx::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI_FX, ani_set->Get(ANI_SMOKE));
}

void SmokeFx::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - time_FX > time_explosion)
		this->Explosion();
}
void SmokeFx::Explosion()
{
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
}