#pragma once
#include "Canvas.h"
#include "ItemCard.h"
#include "Sprites.h"

#define COURSE_CLEAR  "COURSE CLEAR !"
#define CARD_REWARD  "YOU GOT A CARD "

class RewardCanvas :
    public Canvas
{
    CSprite* items[3];
    D3DXVECTOR2 string1, string2, pos_card;
    ItemCard card;
public:
    RewardCanvas();
    ~RewardCanvas();
    virtual void Update(DWORD dt);
    virtual void Render();
    void setCard(ItemCard typeCard) { card = typeCard; }
};

