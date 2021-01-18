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

public:
	Camera();
	Camera(float width, float height);
	void Load();
	void setCam(float x, float y);
	void setBoundBox(float l, float t, float r, float b);
	void update(float mariox, float marioy);
	void setCamdefault(float x, float y);
	void BlockCam() { blockcam = true; }
	void UnBlockCam() { blockcam = false; }
};

typedef Camera* LPCamera;