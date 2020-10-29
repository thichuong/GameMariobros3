#include "SmallMario.h"
#include "Game.h"

void SmallMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	UpdateVx();
	if (CGame::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		if (Mariostate.movement == MoveStates::Run && Mariostate.jump == JumpStates::Jump && canHighjump)
			SetJumpState(JumpStates::Super);
		if (Mariostate.jump == JumpStates::Jump && canHighjump)
		{
			vy -= MARIO_JUMP_SPEED_Y_SPEED * dt;
			if (vy < -MARIO_JUMP_SPEED_Y_HIGH)
				canHighjump = FALSE;

		}
		else if (Mariostate.jump == JumpStates::Super && canHighjump)
		{
			vy -= MARIO_JUMP_SPEED_Y_SPEED * dt;
			if (vy < -MARIO_JUMP_SPEED_Y_SUPER)
				canHighjump = FALSE;
		}
	}
	vy += MARIO_GRAVITY * dt;
	CMario::Update(dt, colliable_objects);
}
void SmallMario::Render()
{
	//CMario::Render();
	string ani = "";
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
			ani = FALL;
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
				ani = IDLE;
			if (Mariostate.movement == MoveStates::Run)
				ani = RUN;
		}
	}
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, ani_left);
}
void SmallMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left =x;
	top = y;
	right = x + MARIO_SMALL_BBOX_WIDTH;
	bottom = y + MARIO_SMALL_BBOX_HEIGHT;
}
void SmallMario::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(RUN, ani_set->Get("ani-small-mario-high-speed"));
	animations->Add(WALK, ani_set->Get("ani-small-mario-walk"));
	animations->Add(JUMP, ani_set->Get("ani-small-mario-jump"));
	animations->Add(FLY, ani_set->Get("ani-small-mario-high-jump"));
	animations->Add(FALL, ani_set->Get("ani-small-mario-fall"));
	animations->Add(IDLE, ani_set->Get("ani-small-mario-idle"));
	animations->Add(SKID, ani_set->Get("ani-small-mario-skid"));
	animations->Add(CROUCH, ani_set->Get("ani-small-mario-crouch"));
}
void SmallMario::KeyState(BYTE* state)
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
	else if (CGame::GetInstance()->IsKeyDown(DIK_DOWN))
	{
		if (Mariostate.jump == JumpStates::Stand)
		{
		}

	}
	else SetMoveState(MoveStates::Idle);

	if (CGame::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		if (onGround && Mariostate.jump == JumpStates::Stand)
		{
			SetJumpState(JumpStates::Jump);
			onGround = FALSE;
		}
	}
	ChangeState();
}