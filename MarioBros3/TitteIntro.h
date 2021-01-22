#pragma once
#include "Animations.h"
#include "Textures.h"

#define ANI_THREE "ani-three"
#define ANI_TITTE	"ani-title"


class TitteIntro
{
	D3DXVECTOR2 Position;

	ULONGLONG time;
	LPSPRITE ArrowSprite, OptionsSprite;
	CAnimations* animations;
	D3DXVECTOR2 Three, Titte, Arrow, Options;

public:
	TitteIntro();
	void setAnimation(CAnimations* ani_set);
	void Update(DWORD dt);
	void SetPosition(D3DXVECTOR2 Pos) { this->Position = Pos; }
	void Render();

};

