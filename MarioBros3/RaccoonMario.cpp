#include "RaccoonMario.h"
#include "CollisionBox.h"
#include "Game.h"
#include "Goomba.h"
#include "Utils.h"

RaccoonMario::RaccoonMario() :CMario()
{
	collision = CCollision::Full;
	tail = NULL;
	timecooldown = RACCOONMARIO_TIMECOOLDOWN;
	ani_timeattack = RACCOONMARIO_ANI_ATTACKTIME;
	timeattack = RACCOONMARIO_TIMECOOLDOWN;
}
void RaccoonMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	UpdateVx();
	if (CGame::GetInstance()->IsKeyDown(DIK_S))
	{
		if (metter == MAX_METTER && Mariostate.jump == JumpStates::Jump && canHighjump)
			SetJumpState(JumpStates::Super);
		if (Mariostate.jump == JumpStates::Jump && canHighjump)
		{
			vy -= MARIO_JUMP_SPEED_Y_UP * dt;
			if (vy < -MARIO_JUMP_SPEED_Y_HIGH)
				canHighjump = FALSE;
		}
		else if (Mariostate.jump == JumpStates::Super && canHighjump)
		{
			vy -= MARIO_JUMP_SPEED_Y_UP * dt;
			if (vy < -MARIO_FLY_SPEED_Y)
				canHighjump = FALSE;
		}
		else
			if (vy > 0)
			{			
				vy = MARIO_GRAVITY * dt;
				slowFall = TRUE;
			}
				
	}
	vy += MARIO_GRAVITY * dt;
	CMario::Update(dt, colliable_objects);
	if ((CGame::GetInstance()->IsKeyDown(DIK_Z) || attack == TRUE) && player->holdobject == NULL)
	{
		SetMoveState(MoveStates::Attack);
		
	}
	if (timeattack >= 0 && timeattack <= RACCOONMARIO_ATTACKTIME)
	{
		if (tail == NULL) tail = new MarioTail(x, y);
		tail->SetPosition(x - MARIO_BIG_BBOX_WIDTH, y + MARIO_BIG_BBOX_HEIGHT / 2);
		tail->Update(dt, colliable_objects);
	}
	else 
	{
		if (tail != NULL)
		{
			delete tail;
			tail = NULL;
		}
	}
	
}

void RaccoonMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	if (Mariostate.movement != MoveStates::Crouch)
	{
		left = x;
		top = y;
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else
	{
		left = x;
		top = y + MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT_CROUCHING;
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT_CROUCHING;
	}
}
void  RaccoonMario::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(RUN, ani_set->Get("ani-raccoon-mario-speed-up"));
	animations->Add(WALK, ani_set->Get("ani-raccoon-mario-walk"));
	animations->Add(JUMP, ani_set->Get("ani-raccoon-mario-jump"));
	animations->Add(FLY, ani_set->Get("ani-raccoon-mario-fly"));
	animations->Add(FALL, ani_set->Get("ani-raccoon-mario-fall"));
	animations->Add(FLOAT, ani_set->Get("ani-raccoon-mario-float"));
	animations->Add(IDLE, ani_set->Get("ani-raccoon-mario-idle"));
	animations->Add(SKID, ani_set->Get("ani-raccoon-mario-skid"));
	animations->Add(CROUCH, ani_set->Get("ani-raccoon-mario-crouch"));
	animations->Add(ATTACK, ani_set->Get("ani-raccoon-mario-spin"));
	animations->Add(HOLD, ani_set->Get("ani-raccoon-mario-hold"));
	animations->Add(HOLD_IDLE, ani_set->Get("ani-raccoon-mario-hold-idle"));
	animations->Add(HOLD_FALL, ani_set->Get("ani-raccoon-mario-hold-fall"));
}
void RaccoonMario::TailAttack(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	CCollisionBox* tail = new CCollisionBox(x , y , MARIO_BIG_BBOX_WIDTH * 2, MARIO_BIG_BBOX_HEIGHT / 2);
	tail->SetPosition(x - MARIO_BIG_BBOX_WIDTH/2, y + MARIO_BIG_BBOX_HEIGHT/2);
	vector<LPGAMEOBJECT> coObjectsResult;

	tail->CalcCollisions(colliable_objects, coObjectsResult);
	//DebugOut(L"	[coObjectsResult] = : %d \n", coObjectsResult.size());
	//DebugOut(L"	[coObjectsResult] MArio  : %f \n", x);
	//DebugOut(L"	[coObjectsResult] taik  : %f \n", tail->x);
	for (UINT i = 0; i < coObjectsResult.size(); i++)
	{
		LPGAMEOBJECT e = coObjectsResult[i];

		if (e->typeobject == TypeObject::enemy) // if e->obj is Goomba 
		{
			float nx = this->x > e->x ? -1 : 1;
			e->CollisionObject(tail,nx,0);
		}
	}
	coObjectsResult.clear();
	delete tail;
}