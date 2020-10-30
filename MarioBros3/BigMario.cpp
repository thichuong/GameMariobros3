#include "BigMario.h"
#include "Game.h"

void BigMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
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

void BigMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	if (Mariostate.movement != MoveStates::Crouch) bottom = y + MARIO_BIG_BBOX_HEIGHT;
	else bottom = y + MARIO_BIG_BBOX_HEIGHT_CROUCHING;
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
}