#include "Brick.h"

void CBrick::Render()
{
	if(animations->Get("ani-brick")!=NULL)
		animations->Get("ani-brick")->Render(x, y);
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
void CBrick::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;

}