#include "RedParatroopa.h"
#include "Game.h"
#include "Mario.h"
#include "RedKoopas.h"

RedParatroopa::RedParatroopa()
{
	SetState(KOOPAS_STATE_WALKING);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	Range = 0;
	tempy = 0;
	vy = KOOPAS_RED_VY;
}

void RedParatroopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	if (x + KOOPAS_BBOX_WIDTH >= camx && x < camx + width)
	{
		CGameObject::Update(dt);
		
		tempy += dy;
		Range += dy;
		if (abs(Range) >= KOOPAS_RED_RANGE)
		{
			if (tempy > 0)
			{
				tempy = KOOPAS_RED_RANGE;
				vy = -KOOPAS_RED_VY;
			}
			else
			{
				tempy = 0;
				vy = KOOPAS_RED_VY;
			}
			Range = 0;
		}

	}
	else return;

	CGame* game = CGame::GetInstance();
	if (y > game->GetScamY() + game->GetScreenHeight() && state == KOOPAS_STATE_DIE) game->GetCurrentScene()->delobject(this);
}
void RedParatroopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + tempy;
	right = x + KOOPAS_BBOX_WIDTH ;
	bottom = y + KOOPAS_BBOX_HEIGHT + tempy;
}
void RedParatroopa::Render()
{
	D3DXVECTOR2 pScale(1, 1);
	string ani = KOOPAS_RED_ANI_TROOPA;
	//CAnimations::GetInstance()->Get(ani)->Render(x, y);
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y - KOOPAS_ANI_Y + tempy, pScale);
	//RenderBoundingBox();
}
void RedParatroopa::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (state == KOOPAS_STATE_DIE) return;
	if (obj->typeobject == TypeObject::player)
	{
		if (ny < 0)
		{
			obj->y -= KOOPAS_FLY;
			obj->vy -= KOOPAS_FLY;
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
			swicth(KOOPAS_STATE_DIE, 0);

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
void RedParatroopa::swicth(int state, float vx)
{
	RedKoopas* koopas = new RedKoopas();
	koopas->SetPosition(x, y);
	koopas->SetState(state);
	koopas->vx = vx;
	if (state == KOOPAS_STATE_DIE || state == KOOPAS_STATE_SHELL)
		koopas->vy = -KOOPAS_FLY;

	CGame::GetInstance()->GetCurrentScene()->delobject(this);
	CGame::GetInstance()->GetCurrentScene()->addobject(koopas);
}