#include "Reward.h"
#include "Game.h"
#include "RewardFX.h"
#include "ScoreFx.h"
#include "RewardCanvas.h"
#include "Player.h"
Reward::Reward(float l, float t) :CGameObject()
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
		ItemCard itemcard = ItemCard::empty;
		RewardFX* rewardFX = new RewardFX(reward);
		rewardFX->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->addobject(rewardFX);
		ActiveGameObject = false;
		RewardCanvas* rewardcanvas = new RewardCanvas();
		if (reward == 0)
			itemcard = ItemCard::mushroom;
		if(reward==1) itemcard = ItemCard::flower;
		if(reward == 2) itemcard = ItemCard::star;

		rewardcanvas->setCard(itemcard);
		CGame::GetInstance()->GetCurrentScene()->addCanvas(rewardcanvas);

		CPlayer* player = CPlayer::GetInstance();
		player->isReWard = TRUE;
		for (int i = 0; i < 3; i++)
		{
			if (player->cards[i].card == ItemCard::empty)
			{
				player->cards[i].card = itemcard;
				break;
			}
		}
		
	}
}
void Reward::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (GetTickCount64() - time_switch > SWITCH_TIME)
	{
		time_switch =(float) GetTickCount64();
		reward += 1;
		if (reward == 3) reward = 0;
	}

}