#include "Plant.h"

#include "Game.h"
#include "Mario.h"
#include "Utils.h"

Plant::Plant()
{
	setPlant();
}
void Plant::setPlant()
{
	SetState(PlantState::hide);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	tempHeight = 0;
	live = true;
	timeLive = TIME_LIFE;
	growTimeMax = TIME_GROW;
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
	if (live)
	{
		CGameObject::Update(dt, coObjects);
		if (idleTime < 0) SetState(PlantState::slidedown);
		if (hideTime < 0) SetState(PlantState::slideup);
		//DebugOut(L"	[Vy] = : %f \n", vy);
		if (plantstate == PlantState::hide) hideTime -= dt;
		if (plantstate == PlantState::idle) idleTime -= dt;

		growTime += dt;
		if (plantstate == PlantState::slidedown || plantstate == PlantState::slideup)
		{

			if (growTime >= growTimeMax)
			{
				if (tempHeight <= maxHeight && plantstate == PlantState::slideup)
				{
					tempHeight = maxHeight;
					SetState(PlantState::idle);
				}
				else if (tempHeight >= 0 && plantstate == PlantState::slidedown)
				{
					tempHeight = 0;
					SetState(PlantState::hide);
				}
			}

		}

		tempHeight += dy;
		//DebugOut(L"	[Venus] = : %f \n", tempHeight);
		//DebugOut(L"	[Time] = : %f \n", hideTime);

	}
	else
	{
		timeLive -= dt;
		
		if (timeLive < 0)
		{
			CGame::GetInstance()->GetCurrentScene()->delobject(this);
			CPlayer::GetInstance()->AddScore(100);
		}
	}
		
	
}


void Plant::SetState(PlantState state)
{
	plantstate = state;
	if (state == PlantState::hide)
	{
		hideTime = TIME_HIDE;
		idleTime = TIME_IDLE;
		growTime = 0;
		vy = 0;
	}
		
	if (state == PlantState::idle)
	{
		idleTime = TIME_IDLE;
		hideTime = TIME_HIDE;
		growTime = 0;
		vy = 0;
	}
	if (state == PlantState::slidedown)
		vy = PLANT_SPEED;
	if (state == PlantState::slideup)
		vy = -PLANT_SPEED;

	//DebugOut(L"	[State] = : %d \n", plantstate);

}
void Plant::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
}

void Plant::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (plantstate == PlantState::hide) return;
	if (obj->typeobject == TypeObject::player)
	{
		obj->DownLevel();	
	}
	else 
	{
		plantstate = PlantState::hide;
		DelObject();
	}
	
}