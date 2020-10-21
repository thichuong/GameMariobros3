#include "CollisionBox.h"
void  CCollisionBox::Render()
{
	
}

void  CCollisionBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BBOX_WIDTH;
	b = y + BBOX_HEIGHT;
}
void  CCollisionBox::SetAnimationSet(CAnimations* ani_set)
{
	
}