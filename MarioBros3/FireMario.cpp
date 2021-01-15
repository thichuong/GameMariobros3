#include "FireMario.h"
#include "Game.h"
#include "FireBullet.h"

FireMario::FireMario() : CMario()
{
	collision = CCollision::Full;
	timecooldown = FIREMARIO_TIMECOOLDOWN;
	ani_timeattack = FIREMARIO_ANI_ATTACKTIME;
	timeattack = FIREMARIO_TIMECOOLDOWN;
	bullets.clear();
}
void FireMario::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
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
			if (vy < -MARIO_JUMP_SPEED_Y_SUPER )
				canHighjump = FALSE;
		}
		else if(Mariostate.movement == MoveStates::Attack && canHighjump)
		{
			vy -= MARIO_JUMP_SPEED_Y_UP * dt;
			if (vy < -MARIO_JUMP_SPEED_Y_HIGH)
				canHighjump = FALSE;

		}
	}
	vy += MARIO_GRAVITY * dt;
	CMario::Update(dt, colliable_objects);
	if ((CGame::GetInstance()->IsKeyDown(DIK_Z) || attack == TRUE) && player->holdobject == NULL && bullets.size() < 2)
	{
		SetMoveState(MoveStates::Attack);
		if (timeattack == 0)
		{
			CFireBullet* firebullet = new CFireBullet(x, y, ax);
			bullets.push_back(firebullet);
			CGame::GetInstance()->GetCurrentScene()->addobject(firebullet);
		}

	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i]->getactive())
		{
			CGame::GetInstance()->GetCurrentScene()->delobject(bullets[i]);
			bullets.erase(bullets.begin() + i);
		}
	}
	
}

void FireMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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
	animations->Add(HOLD, ani_set->Get("ani-fire-mario-hold"));
	animations->Add(HOLD_IDLE, ani_set->Get("ani-fire-mario-hold-idle"));
	animations->Add(HOLD_FALL, ani_set->Get("ani-fire-mario-hold-idle"));
	animations->Add(WARP_HOR_IDLE, ani_set->Get("ani-fire-mario-idle-front"));
}
