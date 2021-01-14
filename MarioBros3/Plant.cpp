#include "Plant.h"

#include "Game.h"
#include "Mario.h"

Plant::Plant()
{
	SetState(PlantState::hide);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	tempHeight = 0;
}

void Plant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y + tempHeight;
	right = x +with;
	bottom = y + height + tempHeight;
	
}

void Plant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	
	if (idleTime < 0) SetState(PlantState::slidedown);
	if (hideTime < 0) SetState(PlantState::slideup);

	if (plantstate == PlantState::hide) hideTime -= dt;
	if (plantstate == PlantState::idle) idleTime -= dt;

	if (plantstate == PlantState::slidedown || plantstate == PlantState::slideup)
	{
		tempHeight += dy;
		if (tempHeight <= maxHeight)
		{
			tempHeight = maxHeight;
			SetState(PlantState::idle);
		}
		if (tempHeight >= 0)
		{
			tempHeight = 0;
			SetState(PlantState::hide);
		}
	}
}

void Plant::Render()
{
	
}

void Plant::SetState(PlantState state)
{
	
	if (state == PlantState::hide)
	{
		hideTime = TIME_HIDE;
		vy = 0;
	}
		
	if (state == PlantState::idle)
	{
		idleTime = TIME_IDLE;
		vy = 0;
	}
	if (state == PlantState::slidedown)
		vy = PLANT_SPEED;
	if (state == PlantState::slideup)
		vy = -PLANT_SPEED;
	plantstate = state;

}
void Plant::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}

void Plant::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	if (plantstate == PlantState::hide) return;
	if (obj->typeobject == TypeObject::player)
	{
		obj->DownLevel();	
	}
	
}