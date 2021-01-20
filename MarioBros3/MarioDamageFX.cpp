#include "MarioDamageFX.h"


MarioDamageFX::MarioDamageFX()
{
	time_FX = GetTickCount64();
	collision = CCollision::None;
	time_explosion = TIME_MARIO_DAMAGE;
	SetAnimationSet(CAnimations::GetInstance());
}
void MarioDamageFX::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI_FX, ani_set->Get(ANI_MARIO_DAMAGE));
}

void MarioDamageFX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - time_FX > time_explosion)
		this->Explosion();
}
void MarioDamageFX::Explosion()
{
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
}