#include "RewardFX.h"
#include "ScoreFx.h"
#include "Player.h"
RewardFX::RewardFX(int reWard)
{
	time_FX = GetTickCount64();
	SetAnimationSet(CAnimations::GetInstance());
	vy = -REWARD_SPEED;
	collision = CCollision::None;
	time_explosion = REWARD_TIME;
	this->reWard = reWard;
	DebugOut(L"[ RewardFX ] \n");
}
void RewardFX::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	if (reWard == 0)
	{
		animations->Add(ANI_FX, ani_set->Get("ani-goal-mushroom"));
	}
	if (reWard == 1)
	{
		animations->Add(ANI_FX, ani_set->Get("ani-goal-flower"));
	}
	if (reWard == 2)
	{
		animations->Add(ANI_FX, ani_set->Get("ani-goal-star"));
	}
	
}
void RewardFX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;
	if (GetTickCount64() - time_FX > time_explosion)
		this->Explosion();
	

}
void RewardFX::Explosion()
{
	
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
	
}