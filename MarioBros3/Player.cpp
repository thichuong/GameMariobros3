#include "Player.h"
#include "Utils.h"


CPlayer::CPlayer()
{
	ListMario[small] = new SmallMario();
	ListMario[big] = new BigMario();
	ListMario[fire] = new FireMario();
	ListMario[raccoon] = new RaccoonMario();
	
	levelMario = big;
	playMario = ListMario[levelMario];
}

CPlayer* CPlayer::__instance = NULL;

CPlayer* CPlayer::GetInstance()
{
	if (__instance == NULL) __instance = new CPlayer();
	return __instance;
}


void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (playMario->GetLevel() != none) SwitchToMario(playMario->GetLevel());
	playMario->Update(dt, colliable_objects);
	playMario->GetPosition(this->x, this->y);
}
void CPlayer::Render()
{
	playMario->Render();
}
void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	playMario->GetBoundingBox(left, top, right, bottom);
}
void CPlayer::SetAnimationSet(CAnimations* ani_set)
{
	ListMario[small]->SetAnimationSet(ani_set);
	ListMario[big]->SetAnimationSet(ani_set);
	ListMario[fire]->SetAnimationSet(ani_set);
	ListMario[raccoon]->SetAnimationSet(ani_set);
	//playMario->SetAnimationSet(ani_set);
}
void CPlayer::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	playMario->SetPosition(x, y);
}
void CPlayer::SwitchToMario(string state)
{
	if (levelMario == small) this->y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT + 0.4;
	levelMario = state;
	playMario->SetLevel(0);
	playMario = ListMario[levelMario];
	playMario->SetPosition(this->x, this->y);
	playMario->StartUntouchable();
	DebugOut(L"[Change playMario]   %s \n", ToLPCWSTR(levelMario));
}