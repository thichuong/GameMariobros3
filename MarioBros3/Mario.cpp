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
	collision = CCollision::Full;
	timecooldown = 0;
	typeobject = TypeObject::player;
	holdobject = NULL;
	hold = false;
}
void CMario::UpdateVx()
{
	if (Mariostate.movement == MoveStates::Run || Mariostate.movement == MoveStates::Walk)
	{
		if ((!CGame::GetInstance()->IsKeyDown(DIK_Z) && Mariostate.jump != JumpStates::Super) || hold ==true)
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
	slowFall = FALSE;

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
//		for (UINT i = 0; i < coEvents.size(); i++)  coObjectsResult.push_back(coEvents[i]->obj);
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
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0; 
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		
		x += min_tx * dx + nx * 0.4;
		y += min_ty * dy + ny * 0.4;

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
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->typeobject == TypeObject::enemy) // if e->obj is Goomba 
			{
				LPGAMEOBJECT obj = e->obj;
				// jump on top >> kill Goomba and deflect a bit 					
				obj->CollisionObject(this, e->nx, e->ny);
				if(e->ny < 0)
					vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
		
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	if (vy > 0)
	{
		onGround = FALSE;
		SetJumpState(JumpStates::Fall);
	}
	
	if (timeattack < timecooldown)
	{
		timeattack += dt;
	}
	if (hold)
	{
		float l, t, r, b;
		if (ax >= 0)
		{
			GetBoundingBox(l, t, r, b);
			holdobject->SetPosition(x + (r - l)- MARIO_HOLD, y +MARIO_SMALL_BBOX_HEIGHT/3);
		}
		else
		{
			holdobject->GetBoundingBox(l, t, r, b);
			holdobject->SetPosition(x - (r - l) + MARIO_HOLD, y + MARIO_SMALL_BBOX_HEIGHT/3);
		}
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
		if (hold)
		{
			ani = HOLD;
		}
		if (ani_timeattack > timeattack)
			ani = ATTACK;
	}
	if (animations->Get(ani) != NULL)
		if (ani == ATTACK)
			animations->Get(ani)->Render(x, y, MARIO_TIME_ATTACK, ani_left);
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

*/
void CMario::OnKeyUp(int keyCode) {
	if (keyCode == DIK_SPACE)
	{
		canHighjump = FALSE;
	}
	if(keyCode == DIK_Z)
	{
		kickObj();
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
	case DIK_1: SetLevel(small);
		break;
	case DIK_2: SetLevel(big);
		break;
	case DIK_3:	SetLevel(fire);
		break;
	case DIK_4: SetLevel(raccoon);
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
	if (e == MoveStates::Attack && timeattack < timecooldown && Mariostate.movement!= MoveStates::Crouch)
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
	if (Mariostate.movement == MoveStates::Attack && timeattack >= timecooldown)
	{
		timeattack = 0;
	}
		
}
void CMario::SetJumpState(JumpStates e)
{
	
	preMariostate = Mariostate; 
	Mariostate.jump = e;

}
void CMario::holdObj(LPGAMEOBJECT obj)
{
	holdobject = obj;
	hold = true;  
	holdobject->collision = CCollision::None;
}
void CMario::kickObj()
{
	if (hold)
	{
		holdobject->collision = CCollision::Full;
		holdobject->CollisionObject(this, 0, 0);
		hold = false;
		holdobject = NULL;
	}
	
}
void CMario::SetLevel(string l)
{
	
	if (l == small)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT + 0.4);
	}
	
	changeMario = l;
	DebugOut(L"[:SET level playMario]   %s \n", ToLPCWSTR(changeMario));
	//StartUntouchable();
}
string CMario::GetLevel()
{
	return changeMario;
}
void CMario::DownLevel()
{
	CGame::GetInstance()->GetCurrentScene()->GetPlayer()->Downlevel();
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

