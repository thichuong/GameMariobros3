#include "Player.h"
#include "Utils.h"
#include "Game.h"


CPlayer::CPlayer()
{
	ListMario[Mario_small] = new SmallMario();
	ListMario[big] = new BigMario();
	ListMario[fire] = new FireMario();
	ListMario[raccoon] = new RaccoonMario();
	mapmario = new MapMario();

	mapmario->setPlayer(this);
	ListMario[Mario_small]->setPlayer(this);
	ListMario[big]->setPlayer(this);
	ListMario[fire]->setPlayer(this);
	ListMario[raccoon]->setPlayer(this);

	holdobject = NULL;
	levelMario = Mario_small;
	playMario = ListMario[levelMario];
	mapmario->levelMario = this->levelMario;
	collision = CCollision::Full;
	typeobject = TypeObject::player;
	downleveltime = DOWN_LEVEL_TIME;

	score = 0;
	life = 4;
	coin = 0;
	reWard_time_start = 0;
	
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
	if (downleveltime < DOWN_LEVEL_TIME) downleveltime += dt;
	if (GetTickCount64() - reWard_time_start <= REWARD_TIME)
	{
		playMario->UpdateReward(dt);
	}
	else
	{
		playMario->UpdateVx(dt);
	}
	playMario->Update(dt, colliable_objects);
	playMario->GetPosition(this->x, this->y);

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i]->getactive())
		{

			bullets[i]->Explosion();
			bullets.erase(bullets.begin() + i);
		}
	}
}
void CPlayer::Render()
{
	playMario->Render();
}
void CPlayer::Pre_Render()
{
	playMario->Pre_Render();
}
void CPlayer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	playMario->GetBoundingBox(left, top, right, bottom);
}
void CPlayer::SetAnimationSet(CAnimations* ani_set)
{
	ListMario[Mario_small]->SetAnimationSet(ani_set);
	ListMario[big]->SetAnimationSet(ani_set);
	ListMario[fire]->SetAnimationSet(ani_set);
	ListMario[raccoon]->SetAnimationSet(ani_set);

	mapmario->SetAnimationSet(ani_set);
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
	if (levelMario == Mario_small) this->y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT + 0.4f;
	if(state == Mario_small) this->y += MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT - 0.4f;
	levelMario = state;
	ListMario[levelMario]->ax = playMario->ax;
	ListMario[levelMario]->vx = playMario->vx;
	ListMario[levelMario]->vy = playMario->vy;
	playMario->SetLevel(none);
	playMario = ListMario[levelMario];
	playMario->SetPosition(this->x, this->y);
	playMario->StartUntouchable();
	DebugOut(L"[Change playMario]   %s \n", ToLPCWSTR(levelMario));
}
void CPlayer::Downlevel()
{
	if (downleveltime >= DOWN_LEVEL_TIME)
	{
		if (levelMario == Mario_small) playMario->SetState(MARIO_STATE_DIE);
		else if (levelMario == big) playMario->SetLevel(Mario_small);
		else playMario->SetLevel(big);
		
		DebugOut(L"[:Downlevel playMario]   %s \n", ToLPCWSTR(levelMario));
		downleveltime = 0;
	}
	
}
void CPlayer::SetLevel(int lv)
{
	if (lv == 4)
		playMario->SetLevel(raccoon);
}
int CPlayer::getMetter()
{
	int metter =(int) playMario->getMetter();
	
	return metter;	
}
void CPlayer::Warp(TypeWarp warp)
{
	playMario->Warp(warp);
}

void CPlayer::AddScore(long x)
{
	this->score += x;
}

void CPlayer::AddCoin(int x)
{
	this->coin += x;
}

void CPlayer::AddLife(int x)
{
	this->life += x;
}

string CPlayer::GetScore()
{
	string string_score = to_string(score);

	while (string_score.length() < 7)
	{
		string_score = "0" + string_score;
	}
	return string_score;
}

string CPlayer::Getcoin()
{
	return to_string(coin);
}

string CPlayer::GetLife()
{
	return to_string(life);
}
