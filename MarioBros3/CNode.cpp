#include "CNode.h"

CNode::CNode()
{
	nodeID =0;
	typenode = TypeNode::Nodenone;
	IDscene =0;
	up = false;
	down = false;
	left = false;
	right = false;
	SetAnimationSet(CAnimations::GetInstance());
}
void CNode::Render()
{
	if (typenode != TypeNode::Nodenone)
	{
		
		spritesNode[(int)typenode]->Draw(x, y, FALSE);
	}
}

void CNode::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + NODE_BBOX_WIDTH;
	b = y + NODE_BBOX_HEIGHT;
}
void CNode::SetAnimationSet(CAnimations* ani_set)
{
	animations = ani_set;
	CSprites* sprite = CSprites::GetInstance();
	
	spritesNode[0] = sprite->Get("spr-start-0");
	spritesNode[1] = sprite->Get("spr-gate-1");
	spritesNode[2] = sprite->Get("spr-gate-2");
	spritesNode[3] = sprite->Get("spr-gate-3");
	spritesNode[4] = sprite->Get("spr-gate-4");
	spritesNode[5] = sprite->Get("spr-gate-5");
	spritesNode[6] = sprite->Get("spr-gate-6");
	spritesNode[7] = sprite->Get("spr-M-0");
		
}
void CNode::CollisionObject(LPGAMEOBJECT obj, float nx, float ny)
{
	if (obj->typeobject == TypeObject::player)
	{
		
	}
}
void CNode::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{

}

void CNode::SetTypeNode(string type)
{
	if (type == "") typenode = TypeNode::Nodenone;
	if (type == "num-0") typenode = TypeNode::start;
	if (type == "num-1") typenode = TypeNode::num1;
	if (type == "num-2") typenode = TypeNode::num2;
	if (type == "num-3") typenode = TypeNode::num3;
	if (type == "num-4") typenode = TypeNode::num4;
	if (type == "num-5") typenode = TypeNode::num5;
	if (type == "num-6") typenode = TypeNode::num6;
}