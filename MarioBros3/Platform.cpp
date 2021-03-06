#include "Platform.h"
#include "Game.h"
#include "Player.h"


Platform::Platform() : CGameObject()
{

	typeobject = TypeObject::normal;
	collision = CCollision::Top;
	SetAnimationSet(CAnimations::GetInstance());

	isGravity = false;
}
void Platform::Render()
{
	animations->Get(PLATFORM_ANI)->Render(x, y);
	RenderBoundingBox();
}

void Platform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLUS;
	t = y;
	r = x + PLATFORM_BOX_WIDTH;
	b = y + PLATFORM_BOX_HEIGHT/2;
}
void Platform::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(PLATFORM_ANI, ani_set->Get("ani-platform"));

}
void Platform::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player && ny < 0)
	{
		vx = 0;
		vy = PLATFORM_GRAVITTY;
		obj->vy = PLATFORM_GRAVITTY * 3;
	}
}
void Platform::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	
		CGameObject::Update(dt);
		x += dx;
		y += dy;
	
	
	
	

}