#include "Piranha.h"
#include "Player.h"
#include "Game.h"

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
	float camx = (float)CGame::GetInstance()->GetScamX();
	float width = (float)CGame::GetInstance()->GetScreenWidth();
	Plant::Update(dt, coObjects);
	if (x >= camx && x < camx + width)
	{
	}
	else return;
	

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


