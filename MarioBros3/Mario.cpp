#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Player.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

CMario::CMario(float x, float y) : CGameObject()
{
	
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	Mariostate.movement = MoveStates::Idle;
	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
	ax = 1;
	changeMario = none;
	collision = CCollision2D::Full;
	timecooldown = 0;
	timeattack = 0;
}
void CMario::UpdateVx()
{
	if (Mariostate.movement == MoveStates::Run || Mariostate.movement == MoveStates::Walk)
	{
		if (!CGame::GetInstance()->IsKeyDown(DIK_Z) && Mariostate.jump != JumpStates::Super)
		{
			if (ax > 0)
			{
				if (vx == 0) vx = MARIO_WALKING_SPEED;
				if (vx + dt * MARIO_WALKING_SPEED_UP < MARIO_WALKING_SPEED)
				{
					if (vx >= 0)
						vx += dt * MARIO_WALKING_SPEED_UP;
					else vx += dt * MARIO_WALKING_SPEED_DOWN ;
				}
				else
				{
					vx = MARIO_WALKING_SPEED;

				}
			}
				
			else
			{
				if (vx == 0) vx =-MARIO_WALKING_SPEED;
				
				if (vx - dt * MARIO_WALKING_SPEED_UP > -MARIO_WALKING_SPEED)
				{
					if (vx <= 0)
						vx -= dt * MARIO_WALKING_SPEED_UP;
					else vx -= dt * MARIO_WALKING_SPEED_DOWN;
				}
				else {
					vx = -MARIO_WALKING_SPEED;
				}
			}
				
		}
		else
		{
				if (ax > 0)
					if (vx + dt * MARIO_WALKING_SPEED_UP < MARIO_RUNING_SPEED)
					{
						if (vx >= 0)
							vx += dt * MARIO_WALKING_SPEED_UP;
						else vx += dt * MARIO_WALKING_SPEED_DOWN;
					}
					else
					{
						vx = MARIO_RUNING_SPEED;
						SetMoveState(MoveStates::Run);
					}
				else
					if (vx - dt * MARIO_WALKING_SPEED_UP > -MARIO_RUNING_SPEED)
					{
						if (vx <= 0)
							vx -= dt * MARIO_WALKING_SPEED_UP;
						else vx -= dt * MARIO_WALKING_SPEED_DOWN;
					}
					else {
						vx = -MARIO_RUNING_SPEED;
						SetMoveState(MoveStates::Run);
					}
		}
	}
	
	else
	{
		if (vx >= MARIO_MIN_SPEED || vx <= -MARIO_MIN_SPEED)
			vx -= dt * MARIO_WALKING_SPEED_DOWN * vx;
		else vx = 0;
	}
//	slowFall = FALSE;

}
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 

	if (CGame::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		if (onGround && Mariostate.jump == JumpStates::Stand)
		{
			SetJumpState(JumpStates::Jump);
			onGround = FALSE;
		}
	}
	CGameObject::Update(dt);
	
	//dx = vx * dt;

	// Simple fall down

	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	vector<LPGAMEOBJECT> coObjectsResult;
	coEvents.clear();
	
	if (x + dx <= 1)
	{
		dx = 0;
		x = 2;
		//DebugOut(L"[INFO] mario position %d, \n", x);
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
			float px = x;
			x += min_ty * dx;
			y += min_ty * dy + ny * 0.4f;
			dy = 0;
			
			//DebugOut(L"		[X]point = : %f \n",px);
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionX(coEvents, coEventsResult, min_tx, nx, rdx);
				//x -= min_ty * dx;
				x += min_tx * dx + nx * 0.4f;
				DebugOut(L"		[X] coEvents.size() = : %d \n", coEvents.size());
			}
			else
			{
				x = px + dx ;
				nx = 0;
			}
			dy = vy * dt;
			
		}
		else
		{
			float py = y ;
			x += min_tx * dx + nx * 0.4f;
			y += min_tx * dy ;
			dx = 0;
			coEvents.clear();
			CalcPotentialCollisions(&coObjectsResult, coEvents);
			if (coEvents.size() > 0)
			{
				FilterCollisionY(coEvents, coEventsResult, min_ty, ny, rdy);
				y += min_ty * dy + ny * 0.4f;
			}
				
			else
			{
				//y-= min_ty * dy + ny * 0.4f;
				y = py + dy;
				ny = 0;
			}
			dx = vx * dt;
			//y += min_ty * dy + ny * 0.4f;
		}
		

		if (nx != 0)
		{
			vx = 0;
			if(Mariostate.movement != MoveStates::Crouch)
				Mariostate.movement = MoveStates::Idle;
		}
		if (ny != 0) {
			vy = 0;
			if (ny < 0)
			{
				onGround = TRUE;
				Mariostate.jump = JumpStates::Stand;
				canHighjump = TRUE;
			}	
		}
 
		
		//
		// Collision logic with other objects
		//
		/*
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
		*/
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	if (vy > 0)
	{
		onGround = FALSE;
		SetJumpState(JumpStates::Fall);
	}
	if (timecooldown > 0)
	{
		timecooldown -= dt;
		timeattack -= dt;
	}
	else
	{
		timecooldown = 0;
	}
}

void CMario::Render()
{
	string ani = IDLE;
	bool ani_left = false;
	if (ax < 0)
		ani_left = TRUE;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
	{

		if (Mariostate.jump == JumpStates::Jump)
			ani = JUMP;
		else if (Mariostate.jump == JumpStates::Super)
		{
			ani = FLY;
		}
		else if (Mariostate.jump == JumpStates::Fall)
		{
			ani = FALL;
			if (slowFall) ani = FLOAT;
		}

		else
		{
			if (Mariostate.movement == MoveStates::Idle)
			{
				if (vx == 0)ani = IDLE;
				else ani = WALK;
			}
			if (Mariostate.movement == MoveStates::Walk)
			{
				if (vx * ax >= 0)
					ani = WALK;
				else
					ani = SKID;
			}
			if (Mariostate.movement == MoveStates::Crouch)
				ani = CROUCH;
			if (Mariostate.movement == MoveStates::Run)
				ani = RUN;
		}
		if ( timeattack > 0)
			ani = ATTACK;
	}
	if (animations->Get(ani) != NULL)
		if (ani == ATTACK)
			animations->Get(ATTACK)->Render(x, y, MARIO_TIME_ATTACK, ani_left);
		else
			animations->Get(ani)->Render(x, y, ani_left);
}

void CMario::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	
	/*animations->Add(MARIO_ANI_BIG_IDLE, ani_set->Get(MARIO_ANI_BIG_IDLE));
	animations->Add(MARIO_ANI_SMALL_IDLE, ani_set->Get(MARIO_ANI_SMALL_IDLE));
	animations->Add(MARIO_ANI_BIG_WALKING, ani_set->Get(MARIO_ANI_BIG_WALKING));
	animations->Add(MARIO_ANI_SMALL_WALKING, ani_set->Get(MARIO_ANI_SMALL_WALKING));
	animations->Add(MARIO_ANI_DIE, ani_set->Get(MARIO_ANI_DIE));*/
	
	animations = ani_set;
}
void CMario::SetState(int state)
{
	CGameObject::SetState(state);
}
/*
void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level != MARIO_LEVEL_SMALL)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		if (Mariostate.movement != MoveStates::Crouch) bottom = y + MARIO_BIG_BBOX_HEIGHT;
		else bottom = y + MARIO_BIG_BBOX_HEIGHT_CROUCHING;
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}
*/
void CMario::OnKeyUp(int keyCode) {
	if (keyCode == DIK_SPACE)
	{
		canHighjump = FALSE;
	}
	/*if (keyCode == DIK_DOWN)
		SetMoveState(MoveStates::Idle);*/
}
void CMario::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_SPACE:
		//SetState(MARIO_STATE_JUMP);
		 if (onGround)
		{
			 SetJumpState(JumpStates::Jump);
			
			//onGround = FALSE;
			//vy = -MARIO_JUMP_SPEED_Y;
		}
		break;
	case DIK_A:
		Reset();
		break;
	case DIK_1: SetLevel(1);
		break;
	case DIK_2: SetLevel(2);
		break;
	case DIK_3:	SetLevel(3);
		break;
	case DIK_4: SetLevel(4);
		break;
	}
	ChangeState();
}
void CMario::KeyState(BYTE* state)
{
	if (GetState() == MARIO_STATE_DIE) return;
	if (CGame::GetInstance()->IsKeyDown(DIK_RIGHT))
	{		
		 SetMoveState(MoveStates::Walk);
		ax = 1;
	}
	//SetState(MARIO_STATE_WALKING_RIGHT);
	else if (CGame::GetInstance()->IsKeyDown(DIK_LEFT))
	{
		
		SetMoveState(MoveStates::Walk);
		ax = -1;
		
	}
	else if(CGame::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		if (Mariostate.jump ==  JumpStates::Stand)
		{
			SetMoveState(MoveStates::Crouch);
		}
			
	}
	else SetMoveState(MoveStates::Idle);

	if (CGame::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		if (onGround && Mariostate.jump == JumpStates::Stand)
		{
			SetJumpState(JumpStates::Jump);
			vy -= MARIO_JUMP_SPEED_Y*dt;
			onGround = FALSE;
		}
	}
	ChangeState();
}
void CMario::ChangeState()
{
	switch (Mariostate.movement)
	{
	case MoveStates::Walk:
		
		break;
	case MoveStates::Idle:
	
		break;   
	}
	switch (Mariostate.jump)
	{
	case JumpStates::Stand:
		canHighjump = TRUE;
		break;
	case JumpStates::Fall:
		canHighjump = FALSE;
		break;
	case JumpStates::Jump:
			if (onGround)
			{
				vy = -MARIO_JUMP_SPEED_Y;
				onGround = FALSE;
				canHighjump = TRUE;
			}
			break;
	case JumpStates::Super:
	{
		//if(canHighjump)
		//	vy = -MARIO_JUMP_SPEED_Y_HIGH;
		//canHighjump = FALSE;
	}
		
	}
}

void  CMario::SetMoveState(MoveStates e) 
{ 
	if (e == MoveStates::Attack && timecooldown > 0)
	{
		return;
	}
	preMariostate = Mariostate;
	Mariostate.movement = e; 
	if (Mariostate.movement == MoveStates::Crouch)
	{
		if (preMariostate.movement != MoveStates::Crouch)
			y += (MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT_CROUCHING - 0.5);
	}
	else
	{
		if (preMariostate.movement == MoveStates::Crouch)
			y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT_CROUCHING + 0.4);
	}
	if (Mariostate.movement == MoveStates::Attack && timecooldown == 0)
	{
		timecooldown = MARIO_TIME_COOLDOWN;
		timeattack = MARIO_TIME_ATTACK;
	}
		
}
void CMario::SetJumpState(JumpStates e)
{
	
	preMariostate = Mariostate; 
	Mariostate.jump = e;

}
void CMario::SetLevel(int l)
{
	
	if (l == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT + 0.4);
	}
	string level;
	switch (l)
	{
	case 0: level = none;
		break;
	case 1: level= small;
		break;
	case 2:level= big;
		break;
	case 3:level= fire;
		break;
	case 4: level=raccoon;
		break;
	}
	changeMario = level;
	//StartUntouchable();
}
string CMario::GetLevel()
{
	return changeMario;
}
/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	//SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

