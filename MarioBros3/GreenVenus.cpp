#include "GreenVenus.h"

GreenVenus::GreenVenus()
{
	Plant::setPlant();
	tempHeight = 0;
	maxHeight = -VENUS_HEIGHT;
	with = VENUS_WIDTH;
	height = VENUS_HEIGHT;
	HeadVenus = D3DXVECTOR2(1, 1);
	growTime = 0;
	canShot = false;
	fireBalls = NULL;
}

void GreenVenus::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(HeadUp, ani_set->Get("ani-green-venus-fire-trap-headup"));
	animations->Add(HeadDown, ani_set->Get("ani-green-venus-fire-trap-headdown"));
	animations->Add(IdleHeadUp, ani_set->Get("ani-green-venus-fire-trap-headup-idle"));
	animations->Add(IdleHeadDown, ani_set->Get("ani-green-venus-fire-trap-headdown-idle"));
}
