#include "Portal.h"
#include "Game.h"

CPortal::CPortal(float l, float t, float r, float b, int scene_id )
{
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r;
	height = b;
	typeobject = TypeObject::item;
	collision = CCollision::Full;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
void CPortal::SetAnimationSet(CAnimations* ani_set)
{
	
}
void CPortal::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	CGame::GetInstance()->GetCurrentScene()->setSwitchID(this->scene_id);
}