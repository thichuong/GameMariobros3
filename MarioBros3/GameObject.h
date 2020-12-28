#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <string>

#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX "-100"		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};

enum class CCollision
{
	Full, 
	Left,
	Top,
	Right,
	Bottom,
	None
};
enum class TypeObject
{
	normal,
	enemy,
	player,
	Bullet,
	block
};
class CGameObject
{
public:

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	float ax;

	int nx;	 
	int wx;

	int state;

	DWORD dt; 
	CCollision collision;
	TypeObject typeobject;
	//CAnimationSet* animation_set;
	CAnimations* animations;
	//LPANIMATION animations;
public:
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }

	void RenderBoundingBox();

	//void SetAnimationSet(CAnimationSet* ani_set) { animation_set = ani_set; }
	

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	bool AABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void CalcCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPGAMEOBJECT>& coObjectsResult);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny, 
		float &rdx, 
		float &rdy);
	void FilterCollisionX(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,float& nx,float& rdx);
	void FilterCollisionY(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_ty,
		float& ny,
		float& rdy);
	CGameObject();
	virtual void CollisionObject(LPGAMEOBJECT obj, int nx, int ny) {};
	virtual void SetAnimationSet(CAnimations* ani_set) {};
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	virtual void DownLevel() {};
	virtual void SetLevel(int lv) {};

	~CGameObject();
};

