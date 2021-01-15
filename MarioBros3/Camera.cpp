#include "Camera.h"
#include "Game.h"
#include "Resource.h"

Camera::Camera()
{
	screen_height = SCREEN_HEIGHT + 1;
	screen_width = SCREEN_WIDTH + 1;
}
Camera::Camera(float width, float height)
{
	screen_height = height;
	screen_width = width;
}
void Camera::setCam(float x, float y)
{
	cam_x = x;
	cam_y = y;
}

void Camera::update(float mariox, float marioy)
{
	float cx, cy;
	float px, py;
	px = mariox;
	py = marioy;

	cx = px - screen_width / 2;
	cy = cam_y;
	
	if (cy > py - screen_height / 5)
	{
		cy = py - screen_height / 5;
		if (cy < 0)
			cy = 0;
	}
	if (cy + screen_height < py + screen_height / 2)
		cy = py - screen_height / 2;
	if (cy > camYdefault)
		cy = camYdefault;
	if (cy + screen_height - py < YHUD) cy += YHUD;
	if (cy <= top) cy = top;
	if (cx + screen_width >= right) cx = right - screen_width;
	if (cx <= left) cx = left;
	if(blockcam)
		setCam(cx, cam_y);
	else
		setCam(cx, cy);
}

void Camera::setCamdefault(float x, float y)
{
	camXdefault = x;
	camYdefault = y;
}
void Camera::setBoundBox(int l, int t, int r, int b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}


