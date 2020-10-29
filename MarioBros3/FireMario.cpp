#include "FireMario.h"
#include "Game.h"

void FireMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
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
			if (vy < -MARIO_JUMP_SPEED_Y_SUPER )
				canHighjump = FALSE;
		}
		else if(Mariostate.movement == MoveStates::Attack && canHighjump)
		{
			vy -= MARIO_JUMP_SPEED_Y_SPEED * dt;
			if (vy < -MARIO_JUMP_SPEED_Y_HIGH)
				canHighjump = FALSE;

		}
	}
	vy += MARIO_GRAVITY * dt;
	CMario::Update(dt, colliable_objects);
	if (CGame::GetInstance()->IsKeyDown(DIK_X) && Mariostate.movement != MoveStates::Crouch)
	{
		SetMoveState(MoveStates::Attack);
	}
}
void FireMario::Render()
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
				ani = CROUCH;
			if (Mariostate.movement == MoveStates::Run)
				ani = RUN;
		}
		if (Mariostate.movement == MoveStates::Attack)
			ani = ATTACK;
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
void FireMario::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(RUN, ani_set->Get("ani-fire-mario-high-speed"));
	animations->Add(WALK, ani_set->Get("ani-fire-mario-walk"));
	animations->Add(JUMP, ani_set->Get("ani-fire-mario-jump"));
	animations->Add(FLY, ani_set->Get("ani-fire-mario-high-jump"));
	animations->Add(FALL, ani_set->Get("ani-fire-mario-fall"));
	animations->Add(IDLE, ani_set->Get("ani-fire-mario-idle"));
	animations->Add(SKID, ani_set->Get("ani-fire-mario-skid"));
	animations->Add(CROUCH, ani_set->Get("ani-fire-mario-crouch"));
	animations->Add(ATTACK, ani_set->Get("ani-fire-mario-throw"));

}
void FireMario::KeyState(BYTE* state)
{
	if (GetState() == MARIO_STATE_DIE) return;
	if (CGame::GetInstance()->IsKeyDown(DIK_X))
	{
		SetMoveState(MoveStates::Attack);
	}
	else
		CMario::KeyState(state);

}