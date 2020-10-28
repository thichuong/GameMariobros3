#include "CollisionBox.h"
CCollisionBox::CCollisionBox(float l, float t, float w, float h)
{
	box_width = w;
	box_height = h;
	if( h > 1) collision = CCollision2D::Full;
	else collision = CCollision2D::Top;
}
void  CCollisionBox::Render()
{
	
}

void  CCollisionBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + box_width;
	b = y + box_height;
}
void  CCollisionBox::SetAnimationSet(CAnimations* ani_set)
{
	
}