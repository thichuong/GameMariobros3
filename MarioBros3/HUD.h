#ifndef __HUD_H__
#define __HUD_H__


#include "UIObject.h"
#include "PMetter.h"
#include "Font.h"
#include "ItemCard.h"
#include "Sprites.h"

class HUD : public UIObject
{
private:
	D3DXVECTOR2 world, life, score, coin, timer;

	PMetter* metter; 

	Font* font;
	CAnimations* animations;

	CSprite* items[4];
	D3DXVECTOR2 cards[3];
public:

	HUD();

	~HUD();

	void Update(DWORD dt); 

	void Render(); 


};

#endif