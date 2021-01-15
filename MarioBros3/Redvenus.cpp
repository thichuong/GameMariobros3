#include "Redvenus.h"
#include "Player.h"
#include "Game.h"
#include "ScoreFx.h"
Redvenus::Redvenus()
{
	Plant::setPlant();
	tempHeight = 0;
	maxHeight = -VENUS_HEIGHT;
	with = VENUS_WIDTH;
	height = VENUS_HEIGHT;
	HeadVenus =  D3DXVECTOR2(1, 1);
	growTime = 0;
}

void Redvenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	if (x + VENUS_WIDTH >= camx*0.8  || x < camx + width*1.2)
	{
	}
	else return;
	Plant::Update(dt, coObjects);
	CPlayer* player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	float mariox ;
	float marioy;
	player->getMario()->GetPosition(mariox, marioy);

	if (mariox < x) HeadVenus.x = 1;
	else HeadVenus.x = -1;

	if (marioy < y + tempHeight) HeadVenus.y = 1;
	else HeadVenus.y = -1;

	float fireBallvy;
	float tempx = abs(mariox - (x + fireBallLocation));
	float tempy = abs(marioy - (y + fireBallLocation + tempHeight));
	fireBallvy = (tempy / tempx);
	if (HeadVenus.y == 1) fireBallvy = -fireBallvy;
	if (idleTime < 400 && canShot)
	{
		addFireBall(fireBallvy);
		canShot = false;
	}
	if (plantstate == PlantState::hide) canShot = true;

}
void Redvenus::Render()
{
	string ani ;
	if (plantstate == PlantState::idle || plantstate == PlantState::hide)
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
	if (live)
	{
		
		if (animations->Get(ani) != NULL)
			animations->Get(ani)->Render(x, y + tempHeight, pScale);
	}
	else
	{
		ani = DIE_ANI;
		if (animations->Get(ani) != NULL)
			animations->Get(ani)->Render(x, y + tempHeight, (DWORD)TIME_LIFE);
	}
	
	
}
void Redvenus::addFireBall(float fireBallvy)
{
	if (fireBalls != NULL)
	{
		CGame::GetInstance()->GetCurrentScene()->delobject(fireBalls);
		fireBalls = NULL;
	}
	int fireBallx, fireBally;
	fireBallx = x + fireBallLocation;
	fireBally = y + fireBallLocation + tempHeight;



	fireBalls = new FireBall(fireBallx, fireBally, -HeadVenus.x, fireBallvy);
	CGame::GetInstance()->GetCurrentScene()->addobject(fireBalls);
}
void Redvenus::DelObject()
{
	if (fireBalls != NULL)
	{
		CGame::GetInstance()->GetCurrentScene()->delobject(fireBalls);
		fireBalls = NULL;
	}
	live = false;
	ScoreFx* fx = new ScoreFx(1);
	fx->SetPosition(x, y);
	CGame::GetInstance()->GetCurrentScene()->addobject(fx);
}