#pragma once
#include "QuestionBlock.h"
class ItemBrick :
    public QuestionBlock
{
public:
    virtual void SetAnimationSet(CAnimations* ani_set) ;
    ItemBrick();
};

