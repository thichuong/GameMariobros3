#pragma once
#include "GameObject.h"
#include "Resource.h"

class WarpMark : public CGameObject
{
	int cameraID;
	TypeWarp typewarp;
	float box_width, box_height;
	int dest_x, dest_y;
	bool block_camera;
public:
	WarpMark(float l, float t, float w, float h);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void setWarp(TypeWarp type) { typewarp = type; }
	void set(int camID, int x, int y)
	{
		cameraID = camID; dest_x = x;  dest_y = y;
	}
	void Block() { block_camera = true; }
	void UnBlock() { block_camera = false; }
};

