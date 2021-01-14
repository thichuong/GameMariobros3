#include "Redvenus.h"


Redvenus::Redvenus()
{
	SetState(PlantState::hide);
	typeobject = TypeObject::enemy;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	tempHeight = 0;
	maxHeight = -VENUS_HEIGHT;
	with = VENUS_WIDTH;
	height = VENUS_HEIGHT;
	HeadVenus =  D3DXVECTOR2(1, 1);
	growTime = 0;
}
void Redvenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Plant::Update(dt, coObjects);
	
}
void Redvenus::Render()
{
	string ani ;
	if (plantstate == PlantState::idle)
	{
		if (HeadVenus.y == 1)
			ani = IdleHeadUp;
		else ani = IdleHeadDown;
	}
	else
	{
		if (HeadVenus.y == 1)
			ani = HeadUp;
		else ani = HeadDown;
	}

	D3DXVECTOR2 pScale = D3DXVECTOR2(HeadVenus.x, 1);
	//ani = "ani-question-block";
	if (animations->Get(ani) != NULL)
		animations->Get(HeadDown)->Render(x, y + tempHeight, pScale);
	
	
}