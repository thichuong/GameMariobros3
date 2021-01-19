#include "RewardCanvas.h"
#include "Game.h"
#include "Textures.h"
RewardCanvas::RewardCanvas()
{
	position = D3DXVECTOR2(0, 0);

	CSprites* sprite = CSprites::GetInstance();

	items[0] = sprite->Get("spr-super-mushroom-card-0");
	items[1] = sprite->Get("spr-fire-flower-card-0");
	items[2] = sprite->Get("spr-star-man-card-0");

	card = ItemCard::empty;

	font = new Font();
	font->setXMLprefix("spr-font-");
	font->LoadFont();

	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	setPosition(D3DXVECTOR2(CGame::GetInstance()->GetScamX() +150, CGame::GetInstance()->GetScamY() + screenHeight * 0.1f));
	string1 = D3DXVECTOR2(position.x + 40, position.y);
	string2 = D3DXVECTOR2(position.x, position.y + 60);
	pos_card = D3DXVECTOR2(position.x + 350, position.y + 40);
}
RewardCanvas::~RewardCanvas()
{

}

void RewardCanvas::Update(DWORD dt)
{
	int screenHeight = CGame::GetInstance()->GetScreenHeight();
	setPosition(D3DXVECTOR2(CGame::GetInstance()->GetScamX() +150, CGame::GetInstance()->GetScamY() + screenHeight * 0.1f));
	string1 = D3DXVECTOR2(position.x + 40, position.y);
	string2 = D3DXVECTOR2(position.x , position.y + 60);
	pos_card = D3DXVECTOR2(position.x + 350, position.y + 40);
}
void RewardCanvas::Render()
{
	
	font->RenderText(COURSE_CLEAR, string1);
	font->RenderText(CARD_REWARD, string2);
	int idCard = 0;
	if (card == ItemCard::mushroom) idCard = 0;
	if (card == ItemCard::flower) idCard = 1;
	if (card == ItemCard::star) idCard = 2;

	items[idCard]->Draw(pos_card.x, pos_card.y, FALSE);
}