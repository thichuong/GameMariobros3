#include "Brick.h"
#include "Game.h"
Brick::Brick(float l, float t)
{
	x = l;
	y = t;
	typeobject = TypeObject::brick;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
}
void Brick::Render()
{
	if (state != Break)
	{
		if (animations->Get("ani-brick") != NULL)
			animations->Get("ani-brick")->Render(x, y);
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
void Brick::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if(obj->typeobject == TypeObject::player && ny >0 )
		CGame::GetInstance()->GetCurrentScene()->delobject(this);
	if(obj->typeobject == TypeObject::normal)
		CGame::GetInstance()->GetCurrentScene()->delobject(this);
}