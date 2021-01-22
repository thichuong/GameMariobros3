#pragma once

#include "Player.h"



class Camera
{
public:
	float cam_x = 0.0f;
	float cam_y = 0.0f;

	float screen_width;
	float screen_height;

	float camYdefault =0;
	float camXdefault =0;

	bool blockcam;

	float left, top, right, bottom;
	float vx;
public:
	Camera();
	Camera(float width, float height);
	void Load();
	void setCam(float x, float y);
	void setBoundBox(float l, float t, float r, float b);
	void getBoundBox(float &l, float &t, float &r, float &b);
	void update(float mariox, float marioy, DWORD dt);
	void setCamdefault(float x, float y);
	void BlockCam() { blockcam = true; }
	void UnBlockCam() { blockcam = false; }
	void setSpeed(float cam_vx) { vx = cam_vx; }
};

typedef Camera* LPCamera;