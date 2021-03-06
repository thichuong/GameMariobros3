#include "BigMario.h"
#include "Game.h"

void BigMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
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

void BigMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
}
void BigMario::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(RUN, ani_set->Get("ani-big-mario-high-speed"));
	animations->Add(WALK, ani_set->Get("ani-big-mario-walk"));
	animations->Add(JUMP, ani_set->Get("ani-big-mario-jump"));
	animations->Add(FLY, ani_set->Get("ani-big-mario-high-jump"));
	animations->Add(FALL, ani_set->Get("ani-big-mario-fall"));
	animations->Add(IDLE, ani_set->Get("ani-big-mario-idle"));
	animations->Add(SKID, ani_set->Get("ani-big-mario-skid"));
	animations->Add(CROUCH, ani_set->Get("ani-big-mario-crouch"));
	animations->Add(HOLD, ani_set->Get("ani-big-mario-hold"));
	animations->Add(HOLD_IDLE, ani_set->Get("ani-big-mario-hold-idle"));
	animations->Add(HOLD_FALL, ani_set->Get("ani-big-mario-hold-idle"));
	animations->Add(WARP_HOR_IDLE, ani_set->Get("ani-big-mario-idle-front"));
}