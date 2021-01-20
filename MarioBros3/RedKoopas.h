#pragma once

#include "Koopas.h"

#define KOOPAS_RED_ANI_WALKING "ani-red-koopa-troopa-move"
#define KOOPAS_RED_ANI_DIE "ani-red-koopa-troopa-crouch"
#define KOOPAS_RED_ANI_SHELL "ani-red-koopa-troopa-shell-idle"
#define KOOPAS_RED_ANI_SHELL_RUN "ani-red-koopa-troopa-shell-run"
#define KOOPAS_RED_ANI_SHELL_CROUCH "ani-red-koopa-troopa-crouch"

class RedKoopas :
    public CKoopas
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	RedKoopas();
};

