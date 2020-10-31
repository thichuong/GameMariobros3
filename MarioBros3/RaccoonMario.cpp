#include "RaccoonMario.h"
#include "Game.h"

RaccoonMario::RaccoonMario() :CMario()
{
	collision = CCollision2D::Full;
	timecooldown = RACCOONMARIO_TIMECOOLDOWN;
	ani_timeattack = RACCOONMARIO_ANI_ATTACKTIME;
	timeattack = RACCOONMARIO_TIMECOOLDOWN;
}
void RaccoonMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
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
	if (CGame::GetInstance()->IsKeyDown(DIK_X))
	{
		SetMoveState(MoveStates::Attack);
	}
}
//void RaccoonMario::Render()
//{
//	//CMario::Render();
//	string ani = "";
//	bool ani_left = false;
//	if (ax < 0)
//		ani_left = TRUE;
//	if (state == MARIO_STATE_DIE)
//		ani = MARIO_ANI_DIE;
//	else
//	{
//		
//		if (Mariostate.jump == JumpStates::Jump)
//			ani = JUMP;
//		else if (Mariostate.jump == JumpStates::Super)
//		{
//			ani = FLY;
//		}
//		else if (Mariostate.jump == JumpStates::Fall)
//		{
//			ani = FALL;
//			if (slowFall) ani = FLOAT;
//		}
//			
//		else
//		{
//			if (Mariostate.movement == MoveStates::Idle)
//			{
//				if (vx == 0)ani = IDLE;
//				else ani = WALK;
//			}
//			if (Mariostate.movement == MoveStates::Walk)
//			{
//				if (vx * ax >= 0)
//					ani = WALK;
//				else
//					ani = SKID;
//			}
//			if (Mariostate.movement == MoveStates::Crouch)
//				ani = CROUCH;
//			if (Mariostate.movement == MoveStates::Run)
//				ani = RUN;
//		}
//		if (Mariostate.movement == MoveStates::Attack)
//			ani = ATTACK;
//	}
//	if (animations->Get(ani) != NULL)
//		if(ani == ATTACK)
//			animations->Get(ani)->Render(x, y,100, ani_left);
//		else
//			animations->Get(ani)->Render(x, y, ani_left);
//}
void RaccoonMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	if (Mariostate.movement != MoveStates::Crouch) bottom = y + MARIO_BIG_BBOX_HEIGHT;
	else bottom = y + MARIO_BIG_BBOX_HEIGHT_CROUCHING;
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
}