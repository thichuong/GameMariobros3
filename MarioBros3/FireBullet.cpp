#include "FireBullet.h"
#include "Animations.h"
#include "Game.h"
#include "Goomba.h"

CFireBullet::CFireBullet(float x, float y, int ax)
{
	this->x = x;
	this->y = y;
	vx = ax * Bullet_SPEED;
	SetAnimationSet(CAnimations::GetInstance());
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

		x += min_tx * dx + nx * 0.4;
		y += min_ty * dy + ny * 0.4;
		if (ny < 0) vy = -Bullet_JUMP;
		if (nx != 0)
		{
			CGame::GetInstance()->GetCurrentScene()->delobject(this);
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				goomba->SetState(GOOMBA_STATE_DIE);
			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}