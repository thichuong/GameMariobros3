#include "Paratroopa.h"
#include "Game.h"
#include "Mario.h"

Paratroopa::Paratroopa()
{
	SetState(KOOPAS_STATE_TROOPA);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
}

void Paratroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state != KOOPAS_STATE_WALKING)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void Paratroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
			y += min_ty * dy + ny * 0.4;
			x += min_tx * dx + nx * 0.4;
		}

		//y += min_ty * dy + ny * 0.5;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			LPGAMEOBJECT obj = e->obj;
			if (e->nx != 0 && e->obj->typeobject == TypeObject::enemy) nx = 0;
		}
		if (ny != 0) {
			vy = -TROOPA_LFY;
		}

		if (nx != 0)
		{
			vx = -vx;
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGame* game = CGame::GetInstance();
	if (y > game->GetScamY() + game->GetScreenHeight() && state == KOOPAS_STATE_DIE) game->GetCurrentScene()->delobject(this);
}

void Paratroopa::Render()
{
	D3DXVECTOR2 pScale(1, 1);
	string ani = KOOPAS_ANI_TROOPA;
	//CAnimations::GetInstance()->Get(ani)->Render(x, y);
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y - KOOPAS_ANI_Y, pScale);
	//RenderBoundingBox();
}

void Paratroopa::SetState(int state)
{
	CGameObject::SetState(state);
	vx = -KOOPAS_WALKING_SPEED;
	collision = CCollision::Full;
	typeobject = TypeObject::enemy;
	

}
void Paratroopa::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}

void Paratroopa::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if (state == KOOPAS_STATE_DIE) return;
	if (obj->typeobject == TypeObject::player)
	{
		if (ny < 0)
		{
			swicth(KOOPAS_STATE_WALKING, vx);
		}
		else
		{
			obj->DownLevel();	
		}
	}
	else
	{
		if (obj->typeobject == TypeObject::Bullet || obj->typeobject == TypeObject::enemy)
		{
			swicth(KOOPAS_STATE_DIE,0);
			
		}
		else if (obj->typeobject != TypeObject::enemy)
		{
			SetState(KOOPAS_STATE_SHELL);
			if (obj->x < this->x) vx = KOOPAS_FLY_SPEED;
			else vx = -KOOPAS_FLY_SPEED;
		
			swicth(KOOPAS_STATE_SHELL, vx);
			
		}
	}
}
void Paratroopa::swicth(int state, float vx)
{
	CKoopas* koopas = new CKoopas();
	koopas->SetPosition(x, y);
	koopas->SetState(state);
	koopas->vx = vx;
	if(state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_SHELL)
		koopas->vy = -KOOPAS_FLY;
	
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
	CGame::GetInstance()->GetCurrentScene()->addobject(koopas);
}