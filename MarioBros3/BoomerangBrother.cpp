#include "BoomerangBrother.h"
#include "Game.h"
#include "Boomerang.h"

BoomerangBrother::BoomerangBrother()
{
	SetState(BoomerangBrother_STATE_WALKING);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	timechangeVX = 0;
	timeattack = 0;
}


void BoomerangBrother::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BoomerangBrother_BBOX_WIDTH;
	bottom = y + BoomerangBrother_BBOX_HEIGHT;
}

void BoomerangBrother::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	if (x + BoomerangBrother_BBOX_WIDTH >= camx && x < camx + width)
	{
		CGameObject::Update(dt);
		vy += BoomerangBrother_GRAVITY * dt;
	}
	else return;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (state != BoomerangBrother_STATE_DIE)
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

		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{

		}

		if (ny != 0)
		{
			vy = 0;
		}
		if (nx != 0)
		{
			vx = -vx;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGame* game = CGame::GetInstance();
		
	if (timechangeVX + dt >= BoomerangBrother_TIME_CHANGE_VX)
	{
		vx = -vx;
		timechangeVX = 0;
	}
	else
	{
		timechangeVX += dt;
	}
	if (timeattack + dt >= BoomerangBrother_TIME_ATTACK)
	{
		timeattack = 0;
		Boomerang* boomerang = new Boomerang(x, y);
		CGame::GetInstance()->GetCurrentScene()->addobject(boomerang);
	}
	else
	{
		timeattack += dt;
	}

	if (y > game->GetScamY() + game->GetScreenHeight() && state == BoomerangBrother_STATE_DIE) game->GetCurrentScene()->delobject(this);
}

void BoomerangBrother::Render()
{
	D3DXVECTOR2 pScale(-1, 1);
	string ani = "ani-boomerang-brother-move";

	if (state == BoomerangBrother_STATE_ATTACK) 
	{
		ani = "ani-boomerang-brother-attack";
	}
	if (state == BoomerangBrother_STATE_DIE)
	{
		pScale = D3DXVECTOR2(-1, -1);
	}

	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, pScale);
	

}

void BoomerangBrother::SetState(int state)
{

	switch (state)
	{
	case BoomerangBrother_STATE_DIE:
		vx = 0;
		collision = CCollision::None;
		
		break;
	case BoomerangBrother_STATE_WALKING:
		vx = -BoomerangBrother_WALKING_SPEED;
		break;
	case BoomerangBrother_STATE_ATTACK:
		
		break;
	}
	CGameObject::SetState(state);
}
void BoomerangBrother::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}
void BoomerangBrother::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	//if (obj->typeobject == TypeObject::enemy) return;
	if (obj->typeobject == TypeObject::player)
	{
		if (ny < 0)
		{
			if (state == BoomerangBrother_STATE_WALKING)
				SetState(BoomerangBrother_STATE_DIE);
			vy = -BoomerangBrother_FLY_DIE;
		}
		else
			obj->DownLevel();
	}
	else if (obj->typeobject != TypeObject::player)
	{
		vy = -BoomerangBrother_FLY_DIE;
		SetState(BoomerangBrother_STATE_DIE);
	}
}