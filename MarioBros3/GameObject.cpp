#include <d3dx9.h>
#include <algorithm>


#include "Utils.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	collision = CCollision2D::Full;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
		{
			float ml, mt, mr, mb;
			e->obj->GetBoundingBox(ml, mt, mr, mb);
			if(e->obj->collision == CCollision2D::Full)
				coEvents.push_back(e);
			else if(e->ny < 0)
				coEvents.push_back(e);


		}
		else
			delete e;
	}
	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}
void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	vector<LPGAMEOBJECT> coObjectsResult;
	for (UINT i = 0; i < coEvents.size(); i++)  coObjectsResult.push_back(coEvents[i]->obj);
	vector<LPCOLLISIONEVENT> coEventsxy;
	float tempx, tempy ;
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;
	nx = 0.0f;
	ny = 0.0f;
	tempx = x;
	tempy = y;
	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
			
		LPCOLLISIONEVENT c = coEvents[i];
		
			if (c->t < min_tx && c->nx != 0) {
				min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
			}

			if (c->t < min_ty && c->ny != 0) {
				min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
			}
	}

	if (min_tx > min_ty)
	{
		float px = x;
		x += min_ty * dx;
		y += min_ty * dy + ny * 0.4f;
		dy = 0;
		coEventsResult.push_back(coEvents[min_iy]);
		//DebugOut(L"		[X]point = : %f \n",px);
		coEventsxy.clear();

		CalcPotentialCollisions(&coObjectsResult, coEventsxy);
		if (coEvents.size() > 0)
		{
			FilterCollisionX(coEventsxy, coEventsResult, min_tx, nx, rdx);
			//x -= min_ty * dx;
			x += min_tx * dx + nx * 0.4f;
			DebugOut(L"		[X] coEvents.size() = : %d \n", coEvents.size());
		}
		else
		{
			x = px + dx;
			nx = 0;
		}
		dy = vy * dt;

	}
	else
	{
		float py = y;
		x += min_tx * dx + nx * 0.4f;
		y += min_tx * dy;
		dx = 0;
		coEventsResult.push_back(coEvents[min_ix]);
		coEventsxy.clear();
		CalcPotentialCollisions(&coObjectsResult, coEventsxy);
		if (coEvents.size() > 0)
		{
			FilterCollisionY(coEventsxy, coEventsResult, min_ty, ny, rdy);
			y += min_ty * dy + ny * 0.4f;
		}

		else
		{
			//y-= min_ty * dy + ny * 0.4f;
			y = py + dy;
			ny = 0;
		}
		dx = vx * dt;
		//y += min_ty * dy + ny * 0.4f;
	}
	x = tempx;
	y = tempy;
	for (UINT i = 0; i < coEventsxy.size(); i++)  coEvents.push_back(coEventsxy[i]);
	
}
void CGameObject::FilterCollisionX(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, 
	float& nx, float& rdx)
{
	float tempx, tempy;
	min_tx = 1.0f;
	int min_ix = -1;
	int min_iy = -1;
	nx = 0.0f;

	for (UINT i = 0; i < coEvents.size(); i++)
	{

		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
}
void CGameObject::FilterCollisionY(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_ty,
	float& ny,  float& rdy)
{
	float tempx, tempy;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;
	nx = 0.0f;
	ny = 0.0f;


	for (UINT i = 0; i < coEvents.size(); i++)
	{

		LPCOLLISIONEVENT c = coEvents[i];
		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(x, y,0, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}


CGameObject::~CGameObject()
{

}