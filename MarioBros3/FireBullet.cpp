#include "FireBullet.h"
#include "Animations.h"
#include "Game.h"
#include "Goomba.h"
#include "SmokeFx.h"

CFireBullet::CFireBullet(float x, float y, float ax)
{
	this->x = x;
	this->y = y;
	vx = ax * Bullet_SPEED;
	SetAnimationSet(CAnimations::GetInstance());
	typeobject = TypeObject::Bullet;
	active = true;
}
void CFireBullet::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI, ani_set->Get("ani-fire-ball"));
}
void CFireBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + Bullet_BBOX_WIDTH;
	b = y + Bullet_BBOX_WIDTH;
}
void CFireBullet::Render()
{
	if (animations->Get(ANI) != NULL)
			animations->Get(ANI)->Render(x, y);
}
void CFireBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;
		if (ny < 0) vy = -Bullet_JUMP;
		if (nx != 0)
		{
			
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->typeobject == TypeObject::enemy) // if e->obj is Goomba 
			{
				LPGAMEOBJECT obj = e->obj;
				obj->CollisionObject(this,e->nx,e->ny);
				active = false;
			}
			else if(e->nx != 0 && nx != 0 ) active = false;
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGame* game = CGame::GetInstance();
	if (y > game->GetScamY() + game->GetScreenHeight()) active = false;
	if(x > game->GetScamX() + game->GetScreenWidth() || x < game->GetScamX() - Bullet_BBOX_WIDTH) 
		active = false;
}
void CFireBullet::Explosion()
{
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
	SmokeFx* fx = new SmokeFx();
	fx->SetPosition(x, y);
	CGame::GetInstance()->GetCurrentScene()->addobject(fx);
}