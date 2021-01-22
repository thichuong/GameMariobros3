#pragma once
#include "Animations.h"
#include "Textures.h"

#define ANI_THREE "ani-three"
#define ANI_TITTE	"ani-title"
#define ANI_CURTAIN "ani-full-curtain-"
#define SPEED_CURTAIN 0.2f
#define MAX_CURTAIN 610.00f


class TitteIntro
{
	D3DXVECTOR2 Position;

	ULONGLONG time;
	LPSPRITE ArrowSprite, OptionsSprite;
	CAnimations* animations;
	D3DXVECTOR2 Three, Titte, Arrow, Options;
	D3DXVECTOR2 curtain;
public:
	TitteIntro();
	void setAnimation(CAnimations* ani_set);
	void Update(DWORD dt);
	void SetPosition(D3DXVECTOR2 Pos) { this->Position = Pos; }
	void Render();

};

