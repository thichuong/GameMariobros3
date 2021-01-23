#include "QuestionBlock.h"
#include "Game.h"
#include "Coin.h"
#include "Leaf.h"
#include "PSwitch.h"

QuestionBlock::QuestionBlock() :CGameObject()
{
	tempx = 0;
	tempy = 0;
	typeobject = TypeObject::block;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	isBounce = FALSE;
	isActive = TRUE;
	vx = 0;
	vy = 0;
}
QuestionBlock::QuestionBlock(float l, float t)
{
	x = l;
	y = t;
	tempx = l;
	tempy = t;
	typeobject = TypeObject::block;
	collision = CCollision::Full;
	SetAnimationSet(CAnimations::GetInstance());
	isBounce = FALSE;
	isActive = TRUE;
	vx = 0;
	vy = 0;
}
void QuestionBlock::Render()
{
	string ani = ANI_ACTIVE;
	if (!isActive) ani = ANI_EMPTY;
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y );
	RenderBoundingBox();
}

void QuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (isBounce)
	{
		r = x +  QuestionBlock_BBOX_WIDTH;
		b = y +  QuestionBlock_BBOX_HEIGHT;
	}
	else
	{
		r = x + QuestionBlock_BBOX_WIDTH;
		b = y + QuestionBlock_BBOX_HEIGHT;
	}

}
void QuestionBlock::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();

	animations->Add(ANI_ACTIVE, ani_set->Get("ani-question-block"));
	animations->Add(ANI_EMPTY, ani_set->Get("ani-empty-block"));

}
void QuestionBlock::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{


	if (obj->typeobject == TypeObject::player && ny > 0 && isActive && !isBounce)
	{
		isBounce = TRUE;
		vy = -BOUNCE_VEL;
		Bounce();
		
	}

	if (obj->typeobject == TypeObject::normal && isActive && !isBounce)
	{
		isBounce = TRUE;
		vy = -BOUNCE_VEL;
		Bounce();
		
	}

}
void QuestionBlock::Bounce()
{
	switch (item)
	{
	case Item::Coin:
	{
		Coin* coin = new Coin(x, y - COIN_BBOX_HEIGHT, TRUE);
		CGame::GetInstance()->GetCurrentScene()->addobject(coin);
	}
	break;
	case Item::Leaf:
	{
		Leaf* leaf = new Leaf(x, y - COIN_BBOX_HEIGHT, TRUE);
		CGame::GetInstance()->GetCurrentScene()->addobject(leaf);
	}
	break;

	case Item::PSwitch:
	{
		PSwitch* pswitch = new PSwitch(x, y);
		CGame::GetInstance()->GetCurrentScene()->addobject(pswitch);
	}
	break;
	}


}
void QuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isBounce)
	{
		CGameObject::Update(dt);
		vy += GRAVITY_QUESTIONBLOCK * dt;
		
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();

		CalcPotentialCollisions(colliable_objects, coEvents);

		if (coEvents.size() == 0)
		{
			
				y += vy * dt;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny = 0;
			float rdx = 0;
			float rdy = 0;

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			
			
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (e->obj->typeobject == TypeObject::enemy && e->ny !=0) // if e->obj is Goomba 
				{
					LPGAMEOBJECT obj = e->obj;
					obj->CollisionObject(this, e->nx, e->ny);
					
				}
			}

		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	if (y  > tempy)
	{
		vy = 0;
		y = tempy;
		x = tempx;
		isBounce = FALSE;
		collision = CCollision::Full;
		quantity--;
		if (quantity <= 0)
			isActive = FALSE;
	}
}

void QuestionBlock::SetQuantity(int qunatity)
{
	this->quantity = quantity;

}
