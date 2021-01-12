#include "Leaf.h"
#include "Game.h"
Leaf::Leaf(float l, float t, bool Fly)
{
	x = l;
	y = t;
	typeobject = TypeObject::normal;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	time = 0;
	vx = LFY_X;
}
void Leaf::Render()
{
	if (animations->Get("ani-super-leaf-red") != NULL)
		animations->Get("ani-super-leaf-red")->Render(x, y);
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
void Leaf::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if (obj->typeobject == TypeObject::player)
	{
		CGame::GetInstance()->GetCurrentScene()->delobject(this);
		obj->SetLevel(4);
	}
		
}
void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
		CGameObject::Update(dt);
		vy = LFY_Y;
		x += dx;
		y += dy;
		time += dt;
		if (time >= TIME)
		{
			time = 1;
			vx = -vx;
		}
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();

		
			CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny = 0;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


			//y += min_ty * dy + ny * 0.5;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				LPGAMEOBJECT obj = e->obj;
				if (e->nx != 0 && e->obj->typeobject == TypeObject::player)
				{
					CGame::GetInstance()->GetCurrentScene()->delobject(this);
					obj->SetLevel(4);
				}
			}
		}
}