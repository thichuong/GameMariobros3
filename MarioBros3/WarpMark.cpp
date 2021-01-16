#include "WarpMark.h"
#include "Game.h"
#include "Camera.h"

WarpMark::WarpMark(float l, float t, float w, float h)
{
	x = l;
	y = t;
	box_width = w;
	box_height = h;
	collision = CCollision::None;
	typeobject = TypeObject::normal;
	block_camera = false;
	dest_x = 1;
	dest_y = 1;
	typewarp = TypeWarp::noWarp;
	cameraID = 0;
}

void  WarpMark::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + box_width;
	b = y + box_height;
}
void  WarpMark::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> coEvents;

	vector<LPGAMEOBJECT> player;

	player.clear();
	coEvents.clear();

	player.push_back(CGame::GetInstance()->GetCurrentScene()->GetPlayer()->getMario());
	CalcCollisions(&player, coEvents);

	if (coEvents.size() == 0)
	{

	}
	else
	{

		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPGAMEOBJECT obj = coEvents[i];

			if (obj->typeobject == TypeObject::player)
			{
					obj->Warp(typewarp);
					obj->SetPosition(dest_x, dest_y);
					//obj->SetPosition(6960, 1200);
					Camera* camera = CGame::GetInstance()->GetCurrentScene()->getCamera(cameraID);
					if (block_camera) camera->BlockCam();
					else camera->UnBlockCam();
					CGame::GetInstance()->SetCam(camera);
			}
		}
	}
}