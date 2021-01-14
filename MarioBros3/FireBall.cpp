#include "FireBall.h"
#include "Game.h"

FireBall::FireBall(float x, float y, int ax, float vy)
{
	this->x = x;
	this->y = y;
	vx = ax * FIRE_SPEED;
	this->vy = vy* FIRE_SPEED;
	SetAnimationSet(CAnimations::GetInstance());
	typeobject = TypeObject::Bullet;
	collision = CCollision::None;
	active = true;
	this->SetAnimationSet(CAnimations::GetInstance());
}
void FireBall::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI, ani_set->Get("ani-fire-ball"));
}
void FireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + Bullet_BBOX_WIDTH;
	b = y + Bullet_BBOX_WIDTH;
}
void FireBall::Render()
{
	if (animations->Get(ANI) != NULL)
		animations->Get(ANI)->Render(x, y);
}
void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
	y += dy;

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
				obj->DownLevel();
			}
		}
	}

}