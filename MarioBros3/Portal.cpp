#include "Portal.h"
#include "Game.h"
#include "Player.h"

CPortal::CPortal(float l, float t, float r, float b, int scene_id ) :CGameObject()
{
	this->scene_id = scene_id;
	x = l; 
	y = t;
	width = r;
	height = b;
	typeobject = TypeObject::item;
	collision = CCollision::Full;
	isReward = false;
	time_tick = 0;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
void CPortal::SetAnimationSet(CAnimations* ani_set)
{
	
}
void CPortal::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	this->isReward = true;
	//CGame::GetInstance()->GetCurrentScene()->setSwitchID(this->scene_id);
}
void CPortal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isReward)
	{
		CPlayer* player = CPlayer::GetInstance();
		time_tick += dt;
		if (time_tick >= 10 && player->time_game > 0 )
		{
			time_tick=0;
		
			player->time_game--;
			player->AddScore(50);
		}
		if (player->time_game == 0)
		{
			if (time_tick >= 1000)
			{
				player->isReWard = false;
				CGame::GetInstance()->GetCurrentScene()->setSwitchID(this->scene_id);
			}
				
		}
	}
}