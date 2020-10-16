#include "Brick.h"

void CBrick::Render()
{
	if(animations->Get("ani-music-box")!=NULL)
		animations->Get("ani-music-box")->Render(x, y);
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
	animations = new CAnimations();
	animations->Add("ani-brick", ani_set->Get("ani-brick"));
}