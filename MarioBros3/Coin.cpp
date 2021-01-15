#include "Coin.h"
#include "Game.h"
#include "CoinFX.h"
Coin::Coin(float l, float t, bool Fly)
{
	x = l;
	y = t;
	typeobject = TypeObject::item;
	collision = CCollision::None;
	SetAnimationSet(CAnimations::GetInstance());
	this->Fly = Fly;
	time = COIN_BBOX_FLY_TIME;
}
void Coin::Render()
{
		if (animations->Get("ani-coin") != NULL)
			animations->Get("ani-coin")->Render(x, y);
}

void Coin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}
void Coin::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;

}
void Coin::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	
}
void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (Fly)
	{
		CoinFX* fx = new CoinFX();
		fx->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->delobject(this);
		CGame::GetInstance()->GetCurrentScene()->addobject(fx);
	}
	else
	{
		vector<LPGAMEOBJECT> coEvents;

		vector<LPGAMEOBJECT> player;

		player.clear();
		coEvents.clear();

		player.push_back(CGame::GetInstance()->GetCurrentScene()->GetPlayer()->getMario());
		CalcCollisions(&player, coEvents);

		if (coEvents.size() == 0)
		{

		}
		else
		{

			for (UINT i = 0; i < coEvents.size(); i++)
			{
				LPGAMEOBJECT obj = coEvents[i];

				if (obj->typeobject == TypeObject::player)
				{
					Fly = true;

				}
			}
		}
	}
	

}