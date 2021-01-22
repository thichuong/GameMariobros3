#include "Boomerang.h"
#include "Player.h"
#include "Game.h"


Boomerang::Boomerang(float x, float y)
{
	this->x = x;
	this->y = y;
	vx = Boomerang_SPEED;
	vy = -Boomerang_VY;
	
	SetAnimationSet(CAnimations::GetInstance());
	typeobject = TypeObject::Bullet;
	collision = CCollision::None;
	active = false;
	this->SetAnimationSet(CAnimations::GetInstance());
	time_shot = 0;
}
void Boomerang::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}
void Boomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + Bullet_BBOX_WIDTH;
	b = y + Bullet_BBOX_WIDTH;
}
void Boomerang::Render()
{
	string ani = "ani-boomerang-spin";
	
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y);
}
void Boomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	if (time_shot + dt >= TIME_CHANG_VY && vy < 0)
	{
		vy = Boomerang_CHANGE_VY;
	}
	if (time_shot + dt >= TIME_CHANG_VX && vx > 0)
	{
		vx = -Boomerang_SPEED;
		vy = 0;
	}
	time_shot += dt;
	int camx = CGame::GetInstance()->GetScamX();
	if (x < camx * 0.9) CGame::GetInstance()->GetCurrentScene()->delobject(this);
}