#include "Brick.h"
#include "Game.h"
#include "DebrisFx.h"
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
void Brick::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player && ny > 0)
		Explosion();
		
	if (obj->typeobject == TypeObject::normal)
		Explosion();
}
void Brick::Explosion()
{
	float velx[4] = { +0.15f, +0.20f, -0.20f, -0.15f };
	float vely[4] = { -0.30f, -0.60f, -0.60f, -0.30f };

	for (int i = 0; i < 4; i++)
	{
		DebrisFx* fx = new DebrisFx();
		fx->SetPosition(x, y);
		fx->setForce(velx[i] , vely[i] );
		CGame::GetInstance()->GetCurrentScene()->addobject(fx);
	}
	CGame::GetInstance()->GetCurrentScene()->delobject(this);
}