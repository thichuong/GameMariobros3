#include "TitteIntro.h"
#include "Utils.h"

TitteIntro::TitteIntro()
{
	Position = D3DXVECTOR2(0, 0);
	time = 0;
	Three = D3DXVECTOR2(0, 0);
	Titte = D3DXVECTOR2(0, 0);
	Arrow = D3DXVECTOR2(0, 0);
	Options = D3DXVECTOR2(0, 0);
	curtain = D3DXVECTOR2(350, 0);
	animations = new CAnimations();
	ArrowSprite = NULL;
	OptionsSprite = NULL;
}

void TitteIntro::setAnimation(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(ANI_THREE, ani_set->Get("ani-three"));
	animations->Add(ANI_TITTE, ani_set->Get("ani-title"));
	animations->Add(ANI_CURTAIN, ani_set->Get("ani-full-curtain-"));
	ArrowSprite = CSprites::GetInstance()->Get("spr-menu-arrow-0");
	OptionsSprite = CSprites::GetInstance()->Get("spr-options-0");
}
void TitteIntro::Update(DWORD dt)
{
	Titte = D3DXVECTOR2(Position.x + 265, Position.y);;
	Three = D3DXVECTOR2(Position.x + 275, Position.y + 217);
	Arrow = D3DXVECTOR2(Position.x + 73, Position.y + 360);
	Options = D3DXVECTOR2(Position.x + 250, Position.y + 360);
	float dy = -SPEED_CURTAIN * dt;
	if(curtain.y + dy >= -MAX_CURTAIN)
		curtain = D3DXVECTOR2(curtain.x, curtain.y + dy);
	else curtain = D3DXVECTOR2(curtain.x, -MAX_CURTAIN);
}

void TitteIntro::Render()
{
	animations->Get(ANI_TITTE)->Render(Titte.x, Titte.y, false);
	OptionsSprite->Draw(Options.x, Options.y, FALSE);
	animations->Get(ANI_THREE)->Render(Three.x, Three.y, false);
	ArrowSprite->Draw(Arrow.x, Arrow.y, FALSE);
	animations->Get(ANI_CURTAIN)->Render(curtain.x, curtain.y, false);
	//DebugOut(L"[TILLE RENDER]    \n");
	
}