#include "FXObject.h"


FXObject::FXObject()
{
	time_FX = GetTickCount64();
	collision = CCollision::None;
	time_explosion = 0;
}
void FXObject::SetAnimationSet(CAnimations* ani_set)
{

}
void FXObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetTickCount64() - time_FX > time_explosion)
		this->Explosion();
}

void FXObject::Render()
{
	string ani = ANI_FX;
	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y);

}