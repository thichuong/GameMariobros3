#include "MarioTail.h"
#include "Game.h"
#include "Utils.h"

MarioTail::MarioTail(float x, float y)
{
	collision = CCollision::Top;
	typeobject = TypeObject::normal;
}

void MarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + Tail_BBOX_WIDTH;
	b = y + Tail_BBOX_WIDTH;
}

void MarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> coObjectsResult;

	CalcCollisions(coObjects, coObjectsResult);
	DebugOut(L"	[coObjectsResult] = : %d \n", coObjectsResult.size());
	//DebugOut(L"	[coObjectsResult] MArio  : %f \n", x);
	//DebugOut(L"	[coObjectsResult] taik  : %f \n", tail->x);
	for (UINT i = 0; i < coObjectsResult.size(); i++)
	{
		LPGAMEOBJECT e = coObjectsResult[i];

		if (e->typeobject == TypeObject::enemy) 
		{
			float nx = this->x > e->x ? -1 : 1;
			e->CollisionObject(this, nx, 0);
		}
	}
	coObjectsResult.clear();
}