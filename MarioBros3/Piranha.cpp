#include "Piranha.h"
#include "Player.h"
#include "Game.h"
#include "ScoreFx.h"

Piranha::Piranha()
{
	Plant::setPlant();
	tempHeight = 0;
	maxHeight = -PIRANHA_HEIGHT;
	with = PIRANHA_WIDTH;
	height = PIRANHA_HEIGHT;
	growTime = 0;
}

void Piranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int camx = CGame::GetInstance()->GetScamX();
	int width = CGame::GetInstance()->GetScreenWidth();
	if (x + PIRANHA_WIDTH >= camx * 0.8 || x < camx + width * 1.2)
	{
	}
	else return;
	Plant::Update(dt, coObjects);

}
void Piranha::Pre_Render()
{
	string ani = "ani-green-piranha-plant-attack";
	
	D3DXVECTOR2 pScale = D3DXVECTOR2(1, 1);
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

void Piranha::DelObject()
{
	
	live = false;
	ScoreFx* fx = new ScoreFx(1);
	fx->SetPosition(x, y);
	CGame::GetInstance()->GetCurrentScene()->addobject(fx);
	
}
