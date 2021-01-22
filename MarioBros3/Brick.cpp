#include "Brick.h"
#include "Game.h"
#include "DebrisFx.h"
#include "Player.h"

Brick::Brick(float l, float t) :CGameObject()
{
	x = l;
	y = t;
	typeobject = TypeObject::brick;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	isSwitch = false;
	timeSwitch = 0;
	state = STATE_BRICK;

	CSprites* sprites = CSprites::GetInstance();
	sprite = sprites->Get("spr-coin-3");

}
void Brick::Render()
{
	if (state == STATE_BRICK)
	{
		if (animations->Get("ani-brick") != NULL)
			animations->Get("ani-brick")->Render(x, y);
	}
	else if (state == STATE_COIN)
	{
		sprite->Draw(x, y, FALSE);
	}
}

void Brick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
void Brick::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();

	animations->Add("ani-brick", ani_set->Get("ani-brick"));

}
void Brick::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player && ny > 0)
		Explosion();
		
	if (obj->typeobject == TypeObject::normal)
		Explosion();
}
void Brick::Explosion()
{
	if (state == STATE_BRICK)
	{
		float velx[4] = { +0.15f, +0.20f, -0.20f, -0.15f };
		float vely[4] = { -0.30f, -0.60f, -0.60f, -0.30f };

		for (int i = 0; i < 4; i++)
		{
			DebrisFx* fx = new DebrisFx();
			fx->SetPosition(x, y);
			fx->setForce(velx[i], vely[i]);
			CGame::GetInstance()->GetCurrentScene()->addobject(fx);
		}
		ActiveGameObject = false;
	}
	else if (state == STATE_COIN)
	{
		CPlayer::GetInstance()->AddCoin(1);
		CPlayer::GetInstance()->AddScore(50);
		ActiveGameObject = false;
	}
}
void Brick::SetState(int state)
{
	this->state = state;
	if (isSwitch)
	{
		isSwitch = false;
		timeSwitch = 0;
	}
	else 
	{
		isSwitch = true;
		timeSwitch = GetTickCount64();
	}
	if(state == STATE_BRICK) collision = CCollision::Full;
	else if(state == STATE_COIN) collision = CCollision::None;
}
void Brick::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isSwitch == true)
	{
		if ( GetTickCount64() - timeSwitch >= TIME_SWITCH)
		{
			if(state == STATE_COIN)
				SetState(STATE_BRICK);
			else if (state == STATE_BRICK)
				SetState(STATE_BRICK);
		}
	}
	if (state == STATE_COIN)
	{
		
		vector<LPGAMEOBJECT> coEvents;

		vector<LPGAMEOBJECT> player;

		player.clear();
		coEvents.clear();

		player.push_back(CGame::GetInstance()->GetCurrentScene()->GetPlayer()->getMario());
		CalcCollisions(&player, coEvents);

		if (coEvents.size() == 0)
		{

		}
		else
		{

			for (UINT i = 0; i < coEvents.size(); i++)
			{
				LPGAMEOBJECT obj = coEvents[i];

				if (obj->typeobject == TypeObject::player)
				{
					this->Explosion();
				}
			}
		}
	}
}