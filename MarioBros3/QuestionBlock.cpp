#include "QuestionBlock.h"
#include "Game.h"
#include "Coin.h"
#include "Leaf.h"

QuestionBlock::QuestionBlock(float l, float t)
{
	x = l;
	y = t;
	tempx = x;
	tempy = y;
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
	string ani = "ani-question-block";
	if (!isActive) ani = "ani-empty-block";
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y);
}

void QuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + QuestionBlock_BBOX_WIDTH;
	b = y + QuestionBlock_BBOX_HEIGHT;
}
void QuestionBlock::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;

}
void QuestionBlock::CollisionObject(LPGAMEOBJECT obj, int nx, int ny)
{
	

	if (obj->typeobject == TypeObject::player && ny > 0 && isActive)
	{
		isBounce = TRUE;
		y -= BOUNCE_VEL;
		obj->vy += GRAVITY;
		if (item == Item::Coin)
		{
			Coin* coin = new Coin(x, y - COIN_BBOX_HEIGHT, TRUE);
			CGame::GetInstance()->GetCurrentScene()->addobject(coin);
		}
		else
		{
			Leaf* leaf = new Leaf(x, y - COIN_BBOX_HEIGHT, TRUE);
			CGame::GetInstance()->GetCurrentScene()->addobject(leaf);
		}
	}
		
	if (obj->typeobject == TypeObject::normal && isActive)
	{
		isBounce = TRUE;
		y -= BOUNCE_VEL;
		if (item == Item::Coin)
		{
			Coin* coin= new Coin(x, y - COIN_BBOX_HEIGHT, TRUE);
			CGame::GetInstance()->GetCurrentScene()->addobject(coin);
		}
		else
		{
			Leaf* leaf = new Leaf(x, y - COIN_BBOX_HEIGHT, TRUE);
			CGame::GetInstance()->GetCurrentScene()->addobject(leaf);
		}
		
	}
		

}
void QuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isBounce)
	{
		if (y + vy*dt > tempy)
		{
			vy = 0;
			y = tempy;
			isBounce = FALSE;
			quantity--;
			if(quantity <= 0)
				isActive = FALSE;
		}
		CGameObject::Update(dt);
		vy += GRAVITY * dt;
	}
	
}

void QuestionBlock::SetQuantity(int qunatity)
{
	this->quantity = quantity;
	
}
