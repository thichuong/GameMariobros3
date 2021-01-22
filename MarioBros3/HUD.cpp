#include "HUD.h"
#include "Textures.h"
#include "Game.h"
#include "Player.h"


HUD::HUD()
{

	//hud = CSprites::GetInstance()->Get("spr-hud-0");
	animations = CAnimations::GetInstance();
	metter = new PMetter(); 
	font = new Font();
	font->setXMLprefix("spr-font-");
	font->LoadFont();

	float screenHeight = CGame::GetInstance()->GetScreenHeight();

	world =D3DXVECTOR2(32 + 110, screenHeight - 150 + 24);
	life =D3DXVECTOR2(32 + 110 - 4, screenHeight - 150 + 48);
	score =D3DXVECTOR2(32 + 147, screenHeight - 150 + 48);
	coin =D3DXVECTOR2(32 + 400, screenHeight - 150 + 24);
	timer =D3DXVECTOR2(32 + 375, screenHeight - 150 + 48);

	metter->setPosition(D3DXVECTOR2(32 + 150, screenHeight - 150 + 20));

	CSprites* sprite = CSprites::GetInstance();
	items[0] = sprite->Get("spr-empty-card-0");
	items[1] = sprite->Get("spr-super-mushroom-card-0");
	items[2] = sprite->Get("spr-fire-flower-card-0");
	items[3] = sprite->Get("spr-star-man-card-0");

	for (int i = 0; i < 3; i++)
	{
		cards[i] = D3DXVECTOR2(Position.x + 500 + i*50 , Position.y);
	}
}

HUD::~HUD()
{
}

void HUD::Update(DWORD dt)
{
	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	setPosition(D3DXVECTOR2(CGame::GetInstance()->GetScamX() - 20, CGame::GetInstance()->GetScamY() + screenHeight - 150));
	metter->setPosition(D3DXVECTOR2(Position.x + 190 , Position.y+25));
	metter->Update(dt);
	world = D3DXVECTOR2(Position.x + 150, Position.y + 24);
	life = D3DXVECTOR2(Position.x + 150 - 4, Position.y + 48);
	score = D3DXVECTOR2(Position.x + 197, Position.y + 48);
	coin = D3DXVECTOR2(Position.x + 440, Position.y + 24);
	timer = D3DXVECTOR2(Position.x + 415, Position.y + 48);

	for (int i = 0; i < 3; i++)
	{
		cards[i] = D3DXVECTOR2(Position.x + 540 + i * 80, Position.y);
	}
}

void HUD::Render()
{
	CGame::GetInstance()->Draw((int)Position.x + 300, (int)Position.y - 10,0,0, CTextures::GetInstance()->Get("tex-pannel"), 0, 0, 950, 150);
	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	
	if (animations->Get("ani-hud") != NULL)
		animations->Get("ani-hud")->Render(Position.x+250, Position.y,false);

	font->RenderText("1", world);
	font->RenderText(CPlayer::GetInstance()->GetLife(), life);
	font->RenderText(CPlayer::GetInstance()->GetScore(), score);
	font->RenderText(CPlayer::GetInstance()->Getcoin(), coin);
	font->RenderText(CPlayer::GetInstance()->GetTime(), timer);

	metter->Render();

	for (int i = 0; i < 3; i++)
	{
		int idcard = 0;
		ItemCard item = CPlayer::GetInstance()->cards[i].card;
		if (item == ItemCard::empty)  idcard = 0;
		if (item == ItemCard::mushroom)  idcard = 1;
		if (item == ItemCard::flower)  idcard = 2;
		if (item == ItemCard::star)  idcard = 3;
		items[idcard]->Draw(cards[i].x, cards[i].y, FALSE);
	}

}
