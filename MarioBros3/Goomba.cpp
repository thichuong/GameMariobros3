#include "Goomba.h"
#include "Game.h"

CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	flydie = false;
	timedie = 0;
	SetAnimationSet(CAnimations::GetInstance());
	jumpcount = 0;
	time_jump = 0;
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
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	if (x + GOOMBA_BBOX_WIDTH >= camx || x < camx + width)
	{
		CGameObject::Update(dt);
		vy += GOOMBA_GRAVITY * dt;
	}
	else return;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	if(!flydie)
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
			if (state == GOOMBA_STATE_FLY)
			{

				if (jumpcount < 3 && (GetTickCount() - time_jump) > TIME_JUMP)
				{
					vy += -PARAGOOMBA_LOW_JUMP;
					jumpcount++;
					time_jump = GetTickCount();
				}
				if (jumpcount == 3)
				{
					vy +=-PARAGOOMBA_HIGH_JUMP;

					time_jump = GetTickCount();

					jumpcount = 0;
				}
			}
		}
		if (nx != 0)
		{
			vx = -vx;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	CGame* game = CGame::GetInstance();
	if (state == GOOMBA_STATE_DIE && !flydie)
		if (timedie >= GOOMA_TIME_DIE)
			game->GetCurrentScene()->delobject(this);
		else
		{
			timedie += dt;
			vy = 0;
		}

	if(y > game->GetScamY() + game->GetScreenHeight() && state == GOOMBA_STATE_DIE) game->GetCurrentScene()->delobject(this);
}

void CGoomba::Render()
{
	D3DXVECTOR2 pScale(1, 1);
	string ani = GOOMBA_ANI_WALKING;
	
	if (state == GOOMBA_STATE_DIE) {
		if(!flydie)
			ani = GOOMBA_ANI_DIE;
		else
		{
			ani = GOOMBA_ANI_IDLE;
			pScale.y = -pScale.y;
		}
	}
	

	if(animations->Get( ani)!=NULL)
		animations->Get(ani)->Render(x, y, pScale);
		

}

void CGoomba::SetState(int state)
{
	
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			vx = 0;
			collision = CCollision::None;
			y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE - 0.4f;
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_FLY:
			jumpcount = 0;
			time_jump = GetTickCount64();
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
	CGameObject::SetState(state);
}
void CGoomba::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}
void CGoomba::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	//if (obj->typeobject == TypeObject::enemy) return;
	if (obj->typeobject == TypeObject::player)
	{
		if (ny < 0)
		{
			if(state == GOOMBA_STATE_WALKING)
				SetState(GOOMBA_STATE_DIE);
			else if(state == GOOMBA_STATE_FLY) SetState(GOOMBA_STATE_WALKING);
			vy = 0;
		}			
		else
			obj->DownLevel();
	}
	else if(obj->typeobject != TypeObject::player)
	{
		flydie = TRUE;
		vy = -GOOMBA_FLY_DIE;
		SetState(GOOMBA_STATE_DIE);
	}
}