#include "Coin.h"
#include "Game.h"
#include "CoinFX.h"
#include "ScoreFx.h"
Coin::Coin(float l, float t, bool Fly) :CGameObject()
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

void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	
		
		if (AABBEx(CGame::GetInstance()->GetCurrentScene()->GetPlayer()->getMario()))
		{
			ActiveGameObject = false;
			CPlayer::GetInstance()->AddCoin(1);
			CPlayer::GetInstance()->AddScore(50);
		}
	}
	

}