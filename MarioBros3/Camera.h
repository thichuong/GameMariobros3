#pragma once





class Camera
{
public:
	float cam_x = 0.0f;
	float cam_y = 0.0f;

	int screen_width;
	int screen_height;

	int camYdefault;
	int camXdefault;

	bool blockcam;

	int left, top, right, bottom;

public:
	Camera();
	Camera(float width, float height);
	void Load();
	void setCam(float x, float y);
	void setBoundBox(int l, int t, int r, int b);
	void update(float mariox, float marioy);
	void setCamdefault(float x, float y);
	void BlockCam() { blockcam = true; }
	void UnBlockCam() { blockcam = false; }
};

typedef Camera* LPCamera;