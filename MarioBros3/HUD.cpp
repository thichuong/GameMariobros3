#include "HUD.h"
#include "Textures.h"
#include "Game.h"



HUD::HUD()
{

	//hud = CSprites::GetInstance()->Get("spr-hud-0");
	animations = CAnimations::GetInstance();
	metter = new PMetter(); 

	int screenHeight = CGame::GetInstance()->GetScreenHeight();

	world = D3DXVECTOR2(32 + 110, screenHeight - 150 + 24);
	life = D3DXVECTOR2(32 + 110 - 4, screenHeight - 150 + 48);
	score = D3DXVECTOR2(32 + 147, screenHeight - 150 + 48);
	coin = D3DXVECTOR2(32 + 400, screenHeight - 150 + 24);
	timer = D3DXVECTOR2(32 + 375, screenHeight - 150 + 48);

	metter->setStaticPosition(D3DXVECTOR2(32 + 150, screenHeight - 150 + 20));

}

HUD::~HUD()
{
}

void HUD::Update(DWORD dt)
{
	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	setStaticPosition(D3DXVECTOR2(CGame::GetInstance()->GetScamX() + 20, CGame::GetInstance()->GetScamY() + screenHeight - 100));
	metter->setStaticPosition(D3DXVECTOR2(StaticPosition.x + 150 , StaticPosition.y+25));
}

void HUD::Render()
{
	CGame::GetInstance()->Draw(StaticPosition.x + 250, StaticPosition.y,0, CTextures::GetInstance()->Get("tex-pannel"), 0, 0, 850, 150);
	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	
	if (animations->Get("ani-hud") != NULL)
		animations->Get("ani-hud")->Render(StaticPosition.x+250, StaticPosition.y,false);

	metter->Render();
}
