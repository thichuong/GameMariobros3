#include "Goomba.h"
#include "Game.h"

CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);

}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else 	
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += GOOMBA_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		if (y > 1500) y = 1000;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
	
		y += min_ty * dy + ny * 0.4;
		x += min_tx * dx + nx * 0.4;
		//y += min_ty * dy + ny * 0.5;
		if (ny != 0) vy = 0;
		if (nx != 0)
		{
			vx = -vx;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (state == GOOMBA_STATE_DIE) CGame::GetInstance()->GetCurrentScene()->delobject(this);
	
}

void CGoomba::Render()
{
	string ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE) {
		ani = GOOMBA_ANI_DIE;
	}
	if(animations->Get( ani)!=NULL)
		animations->Get(ani)->Render(x, y);
	//CAnimations::GetInstance()->Get(ani)->Render(x,y);
	//animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
	}
}
void CGoomba::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}