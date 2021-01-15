#include "PMetter.h"
#include "Sprites.h"
#include "Animations.h"
#include "Scence.h"
#include "PlayScence.h"

void PMetter::LoadAnimation()
{
	AddAnimation("P-blink", CAnimations::GetInstance()->Get("ani-p-icon"));
	AddAnimation("Arrow-blink", CAnimations::GetInstance()->Get("ani-arrow-icon"));
	ArrowOn = CSprites::GetInstance()->Get("spr-arrow-icon-white"); 
	ArrowOff = CSprites::GetInstance()->Get("spr-arrow-icon-black");
	P_On = CSprites::GetInstance()->Get("spr-p-icon-white");
	P_Off = CSprites::GetInstance()->Get("spr-p-icon-black");
}

PMetter::PMetter()
{
	this->LoadAnimation();
}

PMetter::~PMetter()
{
}

void PMetter::Update(DWORD dt)
{
	level = CGame::GetInstance()->GetCurrentScene()->GetPlayer()->getMetter();
}

void PMetter::Render()
{
	
	int x = 0;

	for (int i = 0; i < 6; i++)
	{
		
		ArrowOff->Draw(Position.x + x, Position.y,FALSE);
		x += 30;
	}
	P_Off->Draw(Position.x + x, Position.y, FALSE);

	x = 0;
	
	//int level = 6;
	int arrowlevel = level;

	if (arrowlevel >= 7) arrowlevel = 6;

	for (int i = 0; i < arrowlevel; i++)
	{
		ArrowOn->Draw(Position.x + x, Position.y, FALSE);
		x += 30;
	}
	x = 0;
	if (level == 7)
	{
		for (int i = 0; i < arrowlevel; i++)
		{
			animation_set["Arrow-blink"]->Render(Position.x + x, Position.y,false);
			x += 30;
		}
		animation_set["P-blink"]->Render(Position.x + x, Position.y);
	}
	
		
}
