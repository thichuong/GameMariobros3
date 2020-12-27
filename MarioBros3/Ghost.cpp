#include "Ghost.h"

Ghost::Ghost(float l, float t, float w, float h)
{
	x = l;
	y = t; 
	box_width = w;
	box_height = h;
	
	collision = CCollision::Top;

	typeobject = TypeObject::normal;
}
void  Ghost::Render()
{

}

void  Ghost::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + box_width;
	b = y + box_height;
}
void  Ghost::SetAnimationSet(CAnimations* ani_set)
{

}