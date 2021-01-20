#pragma once
#include "Goomba.h"

#define GOOMBA_RED_ANI_WALKING "ani-red-goomba-walk"
#define GOOMBA_RED_ANI_DIE "ani-red-goomba-die"
#define GOOMBA_RED_ANI_IDLE	"ani-red-goomba-idle"
#define GOOMBA_RED_ANI_FLY  "ani-red-para-goomba-fly"


class RedGoomba :
    public CGoomba
{
public:
    RedGoomba();
    virtual void Render();
};

