#include "FireBullet.h"

void CFireBullet::SetAnimationSet(CAnimations* ani_set)
{
	
}
void CFireBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}