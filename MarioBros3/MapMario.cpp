#include "MapMario.h"
#include "Game.h"
#include "CNode.h"

MapMario::MapMario() : CMario()
{
	range = 0;
	isGoing = false;
	up = false;
	down = false;
	left = false;
	right = false;
	tempx = 0;
	tempy = 0;
	complete = false;
}
void MapMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isGoing)
	{
		CGameObject::Update(dt);
		range += dx;
		range += dy;
		if (abs(range)  >= MARIO_MAP_RANGE)
		{
			isGoing = false;
			if (vx > 0)x = tempx + MARIO_MAP_RANGE;
			if (vx < 0) x = tempx - MARIO_MAP_RANGE;
			if (vy > 0) y = tempy + MARIO_MAP_RANGE;
			if (vy < 0) y = tempy - MARIO_MAP_RANGE;
			vx = 0;
			vy = 0;
			dx = 0;
			dy = 0;
			DebugOut(L" [MAPMARIO] x = %f \n", x);
		}
		else
		{
			if (isGoing)
			{
				x += dx;
				y += dy;
				
				
			}

		}
	}
	vector<LPGAMEOBJECT> coObjectsResult;

	CalcCollisions(coObjects, coObjectsResult);
	//DebugOut(L"	[coObjectsResult] MArio  : %f \n", x);
	//DebugOut(L"	[coObjectsResult] taik  : %f \n", tail->x);
	for (UINT i = 0; i < coObjectsResult.size(); i++)
	{
		LPGAMEOBJECT e = coObjectsResult[i];

		if (e->typeobject == TypeObject::node)
		{
			CNode* node = dynamic_cast<CNode*>(e);
			up = node->up;
			down = node->down;
			left = node->left;
			right = node->right;
			if(!isGoing)
				node->GetPosition(x, y);
			if (CGame::GetInstance()->IsKeyDown(DIK_A) && node->getIDscene() != 0)
			{
				CGame::GetInstance()->SwitchScene(node->getIDscene());
			}
			if (this->complete == true)
			{
				this->complete = false;
				node->SetTypeNode("numM");
			}
			//DebugOut(L"[NODE coObjectsResult] = %d , %d, %d , %d \n", up,down,left,right);
			//DebugOut(L"[NODE coObjectsResult] = %d \n", left);
		}

	}
	coObjectsResult.clear();

}

void MapMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{	
		left = x;
		top = y;
		right = x + MARIO_MAP_BBOX_WIDTH;
		bottom = y + MARIO_MAP_BBOX_HEIGHT;
}
void  MapMario::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI_SMALL_MAP, ani_set->Get("ani-small-mario-map"));
	animations->Add(ANI_BIG_MAP, ani_set->Get("ani-big-mario-map"));
	animations->Add(ANI_RACCOON_MAP, ani_set->Get("ani-raccoon-mario-map"));
	animations->Add(ANI_FIRE_MAP, ani_set->Get("ani-fire-mario-map"));
}
void MapMario::Render()
{
	string ani = IDLE;
	
	if (MapMario::levelMario == Mario_small) ani = ANI_SMALL_MAP;
	else if (MapMario::levelMario == big) ani = ANI_BIG_MAP;
	else if (MapMario::levelMario == fire) ani = ANI_FIRE_MAP;
	else if (MapMario::levelMario == raccoon) ani = ANI_RACCOON_MAP;
	animations->Get(ani)->Render(x, y,1000, false);
}
void MapMario::KeyState(BYTE* state)
{
	

}
void MapMario::OnKeyDown(int keyCode)
{
	if (isGoing == false)
	{
		
		range = 0;
		vx = 0;
		vy = 0;
		tempx = x;
		tempy = y;
		isGoing = true;
		switch (keyCode)
		{
		case DIK_RIGHT:
			if(right)
				vx = MARIO_MAP_SPEED;
			else isGoing = false;
			DebugOut(L" [MAPMARIO] going \n");
			break;
		case DIK_LEFT:
			if(left)
				vx = -MARIO_MAP_SPEED;
			else isGoing = false;
			DebugOut(L" [MAPMARIO] going \n");
			break;
		case DIK_DOWN:
			if(down)
				vy = MARIO_MAP_SPEED;
			else isGoing = false;
			DebugOut(L" [MAPMARIO] going \n");
			break;
		case DIK_UP: 
			if(up)
				vy = -MARIO_MAP_SPEED;
			else isGoing = false;
			DebugOut(L" [MAPMARIO] going");
			break;
		}

	}
}