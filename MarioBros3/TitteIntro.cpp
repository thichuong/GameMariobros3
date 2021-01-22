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
	
}

void TitteIntro::setAnimation(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations = ani_set;
	//animations->Add(ANI_THREE, ani_set->Get("ani-three"));
	//animations->Add(ANI_TITTE, ani_set->Get("ani-title"));

	ArrowSprite = CSprites::GetInstance()->Get("spr-menu-arrow-0");
	OptionsSprite = CSprites::GetInstance()->Get("spr-options-0");
}
void TitteIntro::Update(DWORD dt)
{
	Titte = Position;
	Three = D3DXVECTOR2(Position.x + 265, Position.y + 264);
	Arrow = D3DXVECTOR2(Position.x + 73, Position.y + 360);
	Options = D3DXVECTOR2(Position.x + 122, Position.y + 360);
}

void TitteIntro::Render()
{
	animations->Get(ANI_THREE)->Render(Three.x, Three.y, false);
	animations->Get(ANI_TITTE)->Render(Titte.x, Titte.y, false);
	ArrowSprite->Draw(Arrow.x, Arrow.y, FALSE);
	OptionsSprite->Draw(Options.x, Options.y, FALSE);

	//DebugOut(L"[TILLE RENDER]    \n");
	
}