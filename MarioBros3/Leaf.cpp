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
void Leaf::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{	
		CGameObject::Update(dt);
		vy = LFY_Y;
		x += dx;
		y += dy;
		time += dt;
		if (time >= TIME)
		{
			time = 0;
			vx = -LFY_X;
		}
}