#include "Leaf.h"
#include "Game.h"
#include "Player.h"
#include "ScoreFx.h"
Leaf::Leaf(float l, float t, bool Fly) :CGameObject()
{
	x = l;
	y = t;
	typeobject = TypeObject::item;
	collision = CCollision::None;
	SetAnimationSet(CAnimations::GetInstance());
	time = 0;
	vx = LFY_X;
	vy = -LFY_Y_NEW;
}
void Leaf::Render()
{
	string ani = "ani-super-leaf-red";
	D3DXVECTOR2 pScale(1, 1);
	if (vx > 0) pScale.x = 1;
	else pScale.x = -1;
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, pScale);
}

void Leaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + LEAF_BBOX_WIDTH;
	b = y + LEAF_BBOX_HEIGHT;
}
void Leaf::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;

}
void Leaf::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player)
	{
		
	}
		
}
void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
		CGameObject::Update(dt);
		if (vy + LFY_Y * dt >= LFY_Y_NEW)
			vy = LFY_Y;
		else
			vy += LFY_Y * dt;
		x += dx;
		y += dy;
		time += dt;
		if (time >= TIME)
		{
			time = 1;
			vx = -vx;
		}
		vector<LPGAMEOBJECT> coEvents;
		
		vector<LPGAMEOBJECT> player;

		player.clear();		
		coEvents.clear();

		player.push_back(CPlayer::GetInstance()->getMario());
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
					CGame::GetInstance()->GetCurrentScene()->delobject(this);
					obj->SetLevel(4);
					CPlayer::GetInstance()->AddScore(1000);
					ScoreFx* fx = new ScoreFx(5);
					fx->SetPosition(x, y);
					CGame::GetInstance()->GetCurrentScene()->addobject(fx);
				}
			}
		}
	
}