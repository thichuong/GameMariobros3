#include "SmallMario.h"
#include "Game.h"

void SmallMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
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
			if (vy < -MARIO_JUMP_SPEED_Y_SUPER)
				canHighjump = FALSE;
		}
	}
	vy += MARIO_GRAVITY * dt;
	CMario::Update(dt, colliable_objects);

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
	animations->Add(MARIO_ANI_DIE, ani_set->Get("ani-small-mario-die"));
	animations->Add(RUN, ani_set->Get("ani-small-mario-high-speed"));
	animations->Add(WALK, ani_set->Get("ani-small-mario-walk"));
	animations->Add(JUMP, ani_set->Get("ani-small-mario-jump"));
	animations->Add(FLY, ani_set->Get("ani-small-mario-high-jump"));
	animations->Add(FALL, ani_set->Get("ani-small-mario-jump"));
	animations->Add(IDLE, ani_set->Get("ani-small-mario-idle"));
	animations->Add(SKID, ani_set->Get("ani-small-mario-skid"));
	animations->Add(CROUCH, ani_set->Get("ani-small-mario-crouch"));
	animations->Add(HOLD, ani_set->Get("ani-small-mario-hold"));
	animations->Add(HOLD_IDLE, ani_set->Get("ani-small-mario-hold-idle"));
	animations->Add(HOLD_FALL, ani_set->Get("ani-small-mario-hold-fall"));
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

	if (CGame::GetInstance()->IsKeyDown(DIK_S))
	{
		if (onGround && Mariostate.jump == JumpStates::Stand)
		{
			SetJumpState(JumpStates::Jump);
			vy -= MARIO_JUMP_SPEED_Y * dt;
			onGround = FALSE;
		}
	}
	ChangeState();
}