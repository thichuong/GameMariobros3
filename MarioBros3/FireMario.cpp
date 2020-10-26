#include "FireMario.h"
#include "Game.h"

void FireMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (CGame::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		if (abs(vx) == MARIO_RUNING_SPEED && Mariostate.jump == JumpStates::Jump && canHighjump)
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
			if (vy < -MARIO_JUMP_SPEED_Y_SUPER * 0.8)
				canHighjump = FALSE;
		}

	}
	CMario::Update(dt, colliable_objects);
}
void FireMario::Render()
{
	//CMario::Render();
	string ani = "ani";
	bool ani_left = false;
	if (ax < 0)
		ani_left = TRUE;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
	{
		ani += MARIO_ANI_FIRE;
		if (Mariostate.jump == JumpStates::Jump)
			ani += MARIO_ANI_JUMPING;
		else if (Mariostate.jump == JumpStates::Super)
		{
			ani += MARIO_ANI_HIGH_JUMPING;
		}
		else if (Mariostate.jump == JumpStates::Fall)
			ani += MARIO_ANI_FALL;
		else
		{
			if (Mariostate.movement == MoveStates::Idle)
			{
				if (vx == 0)ani += MARIO_ANI_IDLE;
				else ani += MARIO_ANI_WALKING;
			}
			if (Mariostate.movement == MoveStates::Walk)
			{
				if (vx * ax >= 0)
					ani += MARIO_ANI_WALKING;
				else
					ani += MARIO_ANI_SKIDING;
			}
			if (Mariostate.movement == MoveStates::Crouch)
				ani += MARIO_ANI_CROUCHING;
			if (Mariostate.movement == MoveStates::Run)
				ani += MARIO_ANI_RUNING;
		}
	}
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, ani_left);
}
void FireMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	if (Mariostate.movement != MoveStates::Crouch) bottom = y + MARIO_BIG_BBOX_HEIGHT;
	else bottom = y + MARIO_BIG_BBOX_HEIGHT_CROUCHING;
}