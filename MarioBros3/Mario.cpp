#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_BIG;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);

	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
	ax = 0;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	
	if (walking)
	{
		if (ax > 0)
			if (vx <= MARIO_WALKING_SPEED)
			{
				vx += dt * MARIO_WALKING_SPEED_UP;
				if(vx > MARIO_WALKING_SPEED) vx = MARIO_WALKING_SPEED;
			}	
			else vx = MARIO_WALKING_SPEED;
		else
			if (vx >= -MARIO_WALKING_SPEED)
			{
				vx -= dt * MARIO_WALKING_SPEED_UP;
				if(vx < -MARIO_WALKING_SPEED) vx = -MARIO_WALKING_SPEED;
			}	
			else vx = -MARIO_WALKING_SPEED;
	}
	else
	{
		if (vx >= 0.04 || vx <= -0.04)
			vx -= dt * MARIO_WALKING_SPEED_DOWN * vx;
		else vx = 0;
	}
	
	//dx = vx * dt;

	// Simple fall down


	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> coObjectsResult;
	coEvents.clear();
	
	CGameObject::Update(dt);
	vy += MARIO_GRAVITY * dt;
	if (x + dx <= 1)
	{
		//dx = 0;
		x = 2;
		DebugOut(L"[INFO] mario position %d, \n", x);
	}
	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
		for (UINT i = 0; i < coEvents.size(); i++)  coObjectsResult.push_back(coEvents[i]->obj);
	}
		

	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size()==0)
	{
		x += dx; 
		y += dy;
		if (y > 1500)
		{
			y = 1000;
			vy = 0;
		}
			
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0; 
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 
		
		// block every object first!
		
		
		if (min_tx > min_ty)
		{
			x += min_ty * dx;
			y += min_ty * dy + ny * 0.4f;
			dy = 0;
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if(coEvents.size()> 0)
				FilterCollisionX(coEvents, coEventsResult, min_tx, nx,  rdx);
			else
			{
				x-= min_tx * dx + nx * 0.4f;
				x += dx;
			}
			dy = vy * dt;
			x += min_tx * dx + nx * 0.4f;
		}
		else
		{
			x += min_tx * dx + nx * 0.4f;
			y += min_tx * dy ;
			dx = 0;
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
				FilterCollisionY(coEvents, coEventsResult, min_ty, ny, rdy);
			else
			{
				y-= min_ty * dy + ny * 0.4f;
				y += dy;
			}
			dx = vx * dt;
			y += min_ty * dy + ny * 0.4f;
		}
		

		if (nx != 0) vx = 0;	
		if (ny != 0) {
			vy = 0;
			if (ny < 0)
				onGround = TRUE;
		}
 
		
		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState()!= GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable==0)
					{
						if (goomba->GetState()!=GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else 
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CMario::Render()
{
	string ani = string();
	bool ani_left = false;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
	if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			ani = MARIO_ANI_BIG_IDLE;
			if (ax <= 0)  ani_left = TRUE;
		}
		else
		{
			ani = MARIO_ANI_BIG_WALKING;
			if (vx < 0)
				ani_left = TRUE;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (vx == 0)
		{
			ani = MARIO_ANI_SMALL_IDLE;
			if (ax <= 0) ani_left = TRUE;
		}
		else
		{
			ani = MARIO_ANI_SMALL_WALKING;
			if (vx <= 0)
				ani_left = TRUE;
		}
	}
	
	
	//RenderBoundingBox();

	//if (untouchable) alpha = 128;
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, ani_left);

	
}
void CMario::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	
	animations->Add(MARIO_ANI_BIG_IDLE, ani_set->Get(MARIO_ANI_BIG_IDLE));
	animations->Add(MARIO_ANI_SMALL_IDLE, ani_set->Get(MARIO_ANI_SMALL_IDLE));
	animations->Add(MARIO_ANI_BIG_WALKING, ani_set->Get(MARIO_ANI_BIG_WALKING));
	animations->Add(MARIO_ANI_SMALL_WALKING, ani_set->Get(MARIO_ANI_SMALL_WALKING));
	animations->Add(MARIO_ANI_DIE, ani_set->Get(MARIO_ANI_DIE));

	//animations = ani_set;
}
void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		walking = TRUE;
		ax = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		walking = TRUE;
		ax = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (onGround)
		{
			vy = -MARIO_JUMP_SPEED_Y;
			onGround = FALSE;
		}
		break; 
	case MARIO_STATE_IDLE: 
		
		walking = FALSE;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		vx = 0;
		walking = FALSE;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}
void CMario::OnKeyUp(int keyCode) {

}
void CMario::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_SPACE:
		SetState(MARIO_STATE_JUMP);
		Mariostate.jump = JumpStates::Jump;
		break;
	case DIK_A:
		Reset();
		break;
	}
}
void CMario::KeyState(BYTE* state)
{
	if (GetState() == MARIO_STATE_DIE) return;
	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
		SetState(MARIO_STATE_WALKING_RIGHT);
	else if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
		SetState(MARIO_STATE_WALKING_LEFT);
	else
		SetState(MARIO_STATE_IDLE);
}
/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

