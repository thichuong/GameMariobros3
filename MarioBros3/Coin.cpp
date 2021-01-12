#include "Coin.h"
#include "Game.h"
Coin::Coin(float l, float t, bool Fly)
{
	x = l;
	y = t;
	typeobject = TypeObject::block;
	collision = CCollision::Full;
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
	if (obj->typeobject == TypeObject::player)
		CGame::GetInstance()->GetCurrentScene()->delobject(this);
}
void Coin::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (Fly)
	{
		CGameObject::Update(dt);
		y += dy;
		vy -= COIN_BBOX_FLY;
		time -= dt;
		if (time < 0) CGame::GetInstance()->GetCurrentScene()->delobject(this);
	}
}