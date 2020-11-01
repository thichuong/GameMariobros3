#include "Koopas.h"
#include "Game.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	flydie = false;
}

void CKoopas::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state != KOOPAS_STATE_WALKING)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	vy += KOOPAS_GRAVITY * dt;
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if (!flydie)
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
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGame* game = CGame::GetInstance();
	if (state == KOOPAS_STATE_DIE && !flydie) game->GetCurrentScene()->delobject(this);
	if (y > game->GetScamY() + game->GetScreenHeight()) game->GetCurrentScene()->delobject(this);
}

void CKoopas::Render()
{
	D3DXVECTOR2 pScale(1, 1);
	string ani = KOOPAS_ANI_WALKING;
	if (vx > 0)
		pScale.x = -pScale.x;
	if (state == KOOPAS_STATE_DIE) {
		ani = KOOPAS_ANI_DIE;
		pScale.y = -pScale.y;
	}
	if (state == KOOPAS_STATE_SHELL)
		ani = KOOPAS_ANI_SHELL;
	if(state == KOOPAS_STATE_SHELL_RUN)
		ani = KOOPAS_ANI_SHELL_RUN;

	//CAnimations::GetInstance()->Get(ani)->Render(x, y);
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, pScale);
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		//y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		collision = CCollision::None;
		break;
	case KOOPAS_STATE_WALKING:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_SHELL:
		vx = 0;
		break;
	case KOOPAS_STATE_SHELL_RUN:
		break;

	}

}
void CKoopas::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}

void CKoopas::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->typeobject == TypeObject::player)
	{
		if (ny < 0)
		{
			if (state == KOOPAS_STATE_WALKING)
				SetState(KOOPAS_STATE_SHELL);
			else if (state == KOOPAS_STATE_SHELL)
			{
				SetState(KOOPAS_STATE_SHELL_RUN);
				if (obj->x < this->x) vx = KOOPAS_RUN_SPEED;
				else vx = -KOOPAS_RUN_SPEED;
			}
			else if (state == KOOPAS_STATE_SHELL_RUN) SetState(KOOPAS_STATE_SHELL);
		}		
		else
		{
			if (state != KOOPAS_STATE_SHELL)
				obj->DownLevel();
			else 
			{
				SetState(KOOPAS_STATE_SHELL_RUN);
				if (obj->x < this->x) vx = KOOPAS_RUN_SPEED;
				else vx = -KOOPAS_RUN_SPEED;
			}
		}
	}
	else
	{
		if (obj->typeobject == TypeObject::Bullet)
		{
			SetState(KOOPAS_STATE_DIE);
			flydie = true;
			vy = -KOOPAS_FLY;
		}
		else 
		{
			SetState(KOOPAS_STATE_SHELL);
			if (obj->x < this->x) vx = KOOPAS_RUN_SPEED;
			else vx = -KOOPAS_RUN_SPEED;
			vy = -KOOPAS_FLY;
		}
	}
}