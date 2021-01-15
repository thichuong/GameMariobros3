#include "HUD.h"
#include "Textures.h"
#include "Game.h"



HUD::HUD()
{

	//hud = CSprites::GetInstance()->Get("spr-hud-0");
	animations = CAnimations::GetInstance();
	metter = new PMetter(); 
	font = new Font();
	font->setXMLprefix("spr-font-");
	font->LoadFont();

	int screenHeight = CGame::GetInstance()->GetScreenHeight();

	world =D3DXVECTOR2(32 + 110, screenHeight - 150 + 24);
	life =D3DXVECTOR2(32 + 110 - 4, screenHeight - 150 + 48);
	score =D3DXVECTOR2(32 + 147, screenHeight - 150 + 48);
	coin =D3DXVECTOR2(32 + 400, screenHeight - 150 + 24);
	timer =D3DXVECTOR2(32 + 375, screenHeight - 150 + 48);

	metter->setStaticPosition(D3DXVECTOR2(32 + 150, screenHeight - 150 + 20));

}

HUD::~HUD()
{
}

void HUD::Update(DWORD dt)
{
	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	setStaticPosition(D3DXVECTOR2(CGame::GetInstance()->GetScamX() + 20, CGame::GetInstance()->GetScamY() + screenHeight - 150));
	metter->setStaticPosition(D3DXVECTOR2(StaticPosition.x + 190 , StaticPosition.y+25));
	metter->Update(dt);
	world = D3DXVECTOR2(StaticPosition.x + 150, StaticPosition.y + 24);
	life = D3DXVECTOR2(StaticPosition.x + 150 - 4, StaticPosition.y + 48);
	score = D3DXVECTOR2(StaticPosition.x + 197, StaticPosition.y + 48);
	coin = D3DXVECTOR2(StaticPosition.x + 440, StaticPosition.y + 24);
	timer = D3DXVECTOR2(StaticPosition.x + 415, StaticPosition.y + 48);
}

void HUD::Render()
{
	CGame::GetInstance()->Draw(StaticPosition.x + 250, StaticPosition.y,0, CTextures::GetInstance()->Get("tex-pannel"), 0, 0, 850, 150);
	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	
	if (animations->Get("ani-hud") != NULL)
		animations->Get("ani-hud")->Render(StaticPosition.x+250, StaticPosition.y,false);

	font->RenderText("1", world);
	font->RenderText("4", life);
	font->RenderText("0000000", score);
	font->RenderText("00", coin);
	font->RenderText("999", timer);

	metter->Render();
}
