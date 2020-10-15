#include "Brick.h"

void CBrick::Render()
{
	animations= CAnimations::GetInstance()->Get("ani-music-box"); 
	animations->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}