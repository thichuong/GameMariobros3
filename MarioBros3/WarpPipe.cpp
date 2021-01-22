#include "WarpPipe.h"
#include "Game.h"

WarpPipe::WarpPipe(float l, float t, float w, float h) :CGameObject()
{
	x = l;
	y = t;
	box_width = w;
	box_height = h;
	collision = CCollision::None;
	typeobject = TypeObject::normal;
	typewarp = TypeWarp::noWarp;
}

void  WarpPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + box_width;
	b = y + box_height;
}
void  WarpPipe::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
				if (CGame::GetInstance()->IsKeyDown(DIK_DOWN) && typewarp == TypeWarp::down)
					obj->Warp(typewarp);
				if (CGame::GetInstance()->IsKeyDown(DIK_UP) && typewarp == TypeWarp::up)
					obj->Warp(typewarp);
			}
		}
	}
}