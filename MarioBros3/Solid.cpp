#include "Solid.h"

Solid::Solid(float l, float t, float w, float h)
{
	x = l;
	y = t;
	box_width = w;
	box_height = h;
	collision = CCollision::Full;
	typeobject = TypeObject::normal;
}
void  Solid::Render()
{

}

void  Solid::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + box_width;
	b = y + box_height;
}
void  Solid::SetAnimationSet(CAnimations* ani_set)
{

}