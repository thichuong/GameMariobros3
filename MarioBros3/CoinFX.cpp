#include "CoinFX.h"


CoinFX::CoinFX()
{
	time_FX = GetTickCount64();
	SetAnimationSet(CAnimations::GetInstance());
	vy = -COIN_FX_FLY;
	collision = CCollision::None;
	time_explosion = COIN_FX_TIME;
	DebugOut(L"[ CoinFX ] \n");
}
void CoinFX::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI_FX, ani_set->Get("ani-coin"));
}
void CoinFX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;
	if (GetTickCount64() - time_FX > time_explosion)
		this->Explosion();
	if (GetTickCount64() - time_FX > COIN_FX_FLY_TIME)
	{
		vy += dt * COIN_GRAVITY;
	}
	
}
void CoinFX::Explosion()
{
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
}