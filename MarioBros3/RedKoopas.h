#pragma once

#include "Koopas.h"

#define KOOPAS_ANI_WALKING "ani-red-koopa-troopa-move"
#define KOOPAS_ANI_DIE "ani-red-koopa-troopa-crouch"
#define KOOPAS_ANI_SHELL "ani-red-koopa-troopa-crouch"
#define KOOPAS_ANI_SHELL_RUN "ani-red-koopa-troopa-shell-run"

class RedKoopas :
    public CKoopas
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	RedKoopas();
};

