#include "UPMushroom.h"
#include "Game.h"
#include "Player.h"
#include "ScoreFx.h"

UPMushroom::UPMushroom() : Mushroom()
{

}
void UPMushroom::Pre_Render()
{
	string ani = "ani-1-up-mushroom";
	D3DXVECTOR2 pScale(1, 1);

	if (animations->Get(ani) != NULL)
		animations->Get(ani)->Render(x, y, pScale);
}
void UPMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += Mushroom_GRAVITY * dt;
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		y += min_ty * dy + ny * 0.4f;
		x += min_tx * dx + nx * 0.4f;

		if (nx != 0) vx = -vx;
		if (ny != 0) vy = 0;
	}
	CPlayer* player = CPlayer::GetInstance();
	if (AABBEx(player->getMario()))
	{
		player->AddCoin(1);
		player->AddScore(1000);
		player->AddLife(1);
		ScoreFx* fx = new ScoreFx(9);
		fx->SetPosition(x, y);
		CGame::GetInstance()->GetCurrentScene()->addobject(fx);
		CGame::GetInstance()->GetCurrentScene()->delobject(this);
	}
}