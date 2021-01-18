#include "Reward.h"
#include "Game.h"
#include "RewardFX.h"
#include "ScoreFx.h"
Reward::Reward(float l, float t)
{
	x = l;
	y = t;
	typeobject = TypeObject::item;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	time_switch =(float) GetTickCount64();
	reward = 0;
}
void Reward::Render()
{
	items[reward]->Draw(x, y,FALSE);
}

void Reward::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + REWARD_BBOX_X;
	b = y + REWARD_BBOX_Y;
}
void Reward::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
	CSprites* sprite = CSprites::GetInstance();
	
	items[0] = sprite->Get("spr-super-mushroom-0");
	items[1] = sprite->Get("spr-fire-flower-0");
	items[2] = sprite->Get("spr-star-man-0");

}
void Reward::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player)
	{
		RewardFX* rewardFX = new RewardFX(reward);
		rewardFX->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->addobject(rewardFX);
		CGame::GetInstance()->GetCurrentScene()->delobject(this);
	}
}
void Reward::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	
	if (GetTickCount64() - time_switch > SWITCH_TIME)
	{
		time_switch = GetTickCount64();
		reward += 1;
		if (reward == 3) reward = 0;
	}

}