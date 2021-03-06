#include "Camera.h"
#include "Game.h"
#include "Resource.h"
#include "Mario.h"

Camera::Camera()
{
	screen_height = SCREEN_HEIGHT + 1;
	screen_width = SCREEN_WIDTH + 1;
	blockcam = false;
	left = 0; top = 0; right = 0; bottom = 0;
	vx = 0;
}
Camera::Camera(float width, float height)
{
	screen_height = height;
	screen_width = width;
	blockcam = false;
	left = 0; top = 0; right = 0; bottom = 0;
	vx = 0;
}
void Camera::setCam(float x, float y)
{
	cam_x = x;
	cam_y = y;
}

void Camera::update(float mariox, float marioy, DWORD dt)
{
	CPlayer* player = CPlayer::GetInstance();
	float cx, cy;
	float px, py;
	px = mariox;
	py = marioy;
	if (blockcam == false)
	{
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

		if (cx + screen_width >= right) cx = right - screen_width;
		if (cx <= left) cx = left;
		if (cam_y > camYdefault) cam_y = camYdefault;
		setCam(cx, cam_y);

		if (player->getMario()->GetJumpState() == JumpStates::Super)
		{
			setCam(cx, cy);
		}
		else
		{
			if (cam_y < camYdefault)
				setCam(cx, cy);

		}
	}
	else
	{
		float dx = vx * dt;
		float x = cam_x + dx;
		if (x >= right) x = right;
		setCam(x, cam_y);
		//DebugOut(L"[cameras X] = %f \n", x);
	}
	
}

void Camera::setCamdefault(float x, float y)
{
	camXdefault = x;
	camYdefault = y;
}
void Camera::setBoundBox(float l, float t, float r, float b)
{
	left = l;
	top = t;
	right = r;
	bottom = b;
}
void Camera::getBoundBox(float& l, float& t, float& r, float& b)
{
	l = cam_x;
	t = cam_y;
	r = cam_x+screen_width;
	b = cam_y+ screen_height;
}


