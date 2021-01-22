#include "Platform.h"
#include "Game.h"
#include "Player.h"


Platform::Platform() : CGameObject()
{
	
	typeobject = TypeObject::normal;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	width = 0;
	height = 0;
	isGravity =false;
}
void Platform::Render()
{
	animations->Get(PLATFORM_ANI)->Render(x, y, 1000, false);
	RenderBoundingBox();
}

void Platform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
void Platform::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(PLATFORM_ANI, ani_set->Get("ani-platform"));
	
}
void Platform::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player  && ny < 0)
	{
		vx = 0;
		vy = PLATFORM_GRAVITTY;
		obj->vy = PLATFORM_GRAVITTY * 2;
	}
}
void Platform::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	if (x + width >= camx && x <= camx + width*1.1f)
	{
		CGameObject::Update(dt);
		x += dx;
		y += dy;
	}
	

}