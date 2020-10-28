#include "SmallMario.h"
#include "Game.h"

void SmallMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	float maxspeed;
	if (Mariostate.movement == MoveStates::Walk || Mariostate.movement == MoveStates::Run)
	{
		
		if (Mariostate.movement == MoveStates::Run && Mariostate.jump == JumpStates::Stand)
			maxspeed = MARIO_RUNING_SPEED;
		else
			maxspeed = MARIO_WALKING_SPEED;
		if (Mariostate.jump == JumpStates::Super) maxspeed = MARIO_RUNING_SPEED;
		if (ax > 0)
			if (vx + dt * MARIO_WALKING_SPEED_UP < maxspeed)
			{
				if (vx >= 0)
					vx += dt * MARIO_WALKING_SPEED_UP;
				else vx += dt * MARIO_WALKING_SPEED_UP * 0.5;
			}
			else vx = maxspeed;
		else
			if (vx - dt * MARIO_WALKING_SPEED_UP > -maxspeed)
			{
				if (vx <= 0)
					vx -= dt * MARIO_WALKING_SPEED_UP;
				else vx -= dt * MARIO_WALKING_SPEED_UP * 0.5;
			}
			else vx = -maxspeed;
	}
	else
	{
		if (vx >= MARIO_MIN_SPEED || vx <= - MARIO_MIN_SPEED)
			vx -= dt * MARIO_WALKING_SPEED_DOWN * vx;
		else vx = 0;
	}

	if (CGame::GetInstance()->IsKeyDown(DIK_SPACE))
	{
		if (abs(vx) == maxspeed && Mariostate.jump == JumpStates::Jump && canHighjump)
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
				if (vy < -MARIO_JUMP_SPEED_Y_SUPER *0.8)
					canHighjump = FALSE;
		}

	}
	vy += MARIO_GRAVITY * dt;
	CMario::Update(dt, colliable_objects);
}
void SmallMario::Render()
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
		ani += MARIO_ANI_SMALL;
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
				ani += MARIO_ANI_IDLE;
			if (Mariostate.movement == MoveStates::Run)
				ani += MARIO_ANI_RUNING;
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
