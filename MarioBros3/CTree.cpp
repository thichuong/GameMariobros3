#include "CTree.h"

CTree::CTree() : CGameObject()
{
	collision = CCollision::Full;

	typeobject = TypeObject::normal;
}
void CTree::Render()
{
	if (animations->Get(TREE_ANI) != NULL)
		animations->Get(TREE_ANI)->Render(x, y);
}

void CTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + TREE_BBOX_WIDTH;
	b = y + TREE_BBOX_HEIGHT;
}
void CTree::SetAnimationSet(CAnimations* ani_set)
{
	animations = new CAnimations();
	animations->Add(TREE_ANI, ani_set->Get("ani-tree"));

}