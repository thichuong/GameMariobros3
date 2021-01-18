#include "RedKoopas.h"
#include "Game.h"
#include "Mario.h"



RedKoopas::RedKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	FlipY = false;
	SetAnimationSet(CAnimations::GetInstance());
}

void RedKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	/*if (state == KOOPAS_STATE_SHELL_HOLD)
	{
		vx = 0;
		vy = 0;
	}*/

	//OutputDebugStringW(L"[INFO] Object is still alive! \n");
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	if (x + KOOPAS_BBOX_WIDTH >= camx || x < camx + width)
	{
		CGameObject::Update(dt);
		vy += KOOPAS_GRAVITY * dt;
	}
	else return;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();


	if (state != KOOPAS_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		if (state != KOOPAS_STATE_SHELL_HOLD)
		{
			x += dx;
			y += dy;
		}

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		if (state != KOOPAS_STATE_SHELL_HOLD)
		{
			y += min_ty * dy + ny * 0.4f;
			x += min_tx * dx + nx * 0.4f;
		}

		//y += min_ty * dy + ny * 0.5;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			LPGAMEOBJECT obj = e->obj;
			if (state == KOOPAS_STATE_SHELL_RUN || state == KOOPAS_STATE_SHELL_HOLD)
				obj->CollisionObject(this, e->nx, e->ny);
			if (e->nx != 0 && e->obj->typeobject == TypeObject::enemy) nx = 0;
			
			
		}
		if (ny != 0) {
			if (state == KOOPAS_STATE_SHELL)
			{
				vx = 0;
			}
			vy = 0;
		}

		if (nx != 0)
		{
			vx = -vx;
		}
		if (coEvents.size() == 1 && state == KOOPAS_STATE_WALKING)
		{

			LPCOLLISIONEVENT e = coEvents[0];


			LPGAMEOBJECT obj = e->obj;
			if (e->ny < 0)
			{
				float l, t, r, b;
				obj->GetBoundingBox(l, t, r, b);
				if (l - KOOPAS_BBOX_WIDTH / 3 > x || x + KOOPAS_BBOX_WIDTH > r + KOOPAS_BBOX_WIDTH / 3)
				{
					if (l - KOOPAS_BBOX_WIDTH / 3 > x)
					{
						vx = KOOPAS_WALKING_SPEED;
					}
						
					else
					{  
						vx = -KOOPAS_WALKING_SPEED;
					}
				}
			}

		}
	}

	

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGame* game = CGame::GetInstance();
	if (y > game->GetScamY() + game->GetScreenHeight() && state == KOOPAS_STATE_DIE) game->GetCurrentScene()->delobject(this);
}

void RedKoopas::Render()
{
	D3DXVECTOR2 pScale(1, 1);
	string ani = KOOPAS_RED_ANI_WALKING;
	if (vx > 0)
		pScale.x = -pScale.x;
	if (state == KOOPAS_STATE_DIE) {
		ani = KOOPAS_RED_ANI_DIE;

	}
	if (FlipY) pScale.y = -pScale.y;
	if (state == KOOPAS_STATE_SHELL)
		ani = KOOPAS_RED_ANI_SHELL;
	if (state == KOOPAS_STATE_SHELL_RUN)
		ani = KOOPAS_RED_ANI_SHELL_RUN;
	if (state == KOOPAS_STATE_SHELL_HOLD)
		ani = KOOPAS_RED_ANI_SHELL;
	//CAnimations::GetInstance()->Get(ani)->Render(x, y);
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, pScale);
	//RenderBoundingBox();
}