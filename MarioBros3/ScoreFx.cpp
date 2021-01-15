#include "ScoreFx.h"
ScoreFx::ScoreFx( int level)
{
	this->levelScore = level;
	time_FX = GetTickCount64();
	SetAnimationSet(CAnimations::GetInstance());
	vy = -SCORE_FX_FLY;
	collision = CCollision::None;
	time_explosion = SCORE_FX_TIME;
	DebugOut(L"[ ScoreFx ] \n");
}
void ScoreFx::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	string ani = "";
	switch (levelScore)
	{
	case 1: 
		ani = "ani-points-100";
		break;
	case 2: 
		ani = "ani-points-200";
		break;
	case 3:
		ani = "ani-points-400";
		break;
	case 4: 
		ani = "ani-points-800";
		break;
	case 5: 
		ani = "ani-points-1000";
		break;
	case 6:
		ani = "ani-points-2000";
		break;
	case 7: 
		ani = "ani-points-4000";
		break;
	case 8: 
		ani = "ani-points-8000";
		break;
	case 9: 
		ani = "ani-points-1UP";
		break;
	}
	animations->Add(ANI_FX, ani_set->Get(ani));
}
void ScoreFx::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	y += dy;
	if (GetTickCount64() - time_FX > time_explosion)
		this->Explosion();
}
void ScoreFx::Explosion()
{
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
}