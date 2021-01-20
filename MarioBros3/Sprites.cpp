#include "Sprites.h"
#include "Game.h"
#include "Utils.h"

CSprite::CSprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int xPivot, int yPivot)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
	this->xPivot = xPivot;
	this->yPivot = yPivot;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, bool flipx, int alpha)
{
	CGame * game = CGame::GetInstance();
	if (!flipx)
		game->Draw(x, y, xPivot, yPivot,  texture, left, top, right, bottom, alpha);
	else
		//game->Draw(x, y, texture, left, top, right, bottom, alpha);
		game->DrawFlipX(x, y, xPivot, yPivot, texture, left, top, right, bottom, alpha);
}
void CSprite::Draw(float x, float y,D3DXVECTOR2 vectorflip, int alpha)
{
	CGame* game = CGame::GetInstance();
	game->Draw(x, y, xPivot, yPivot, vectorflip, texture, left, top, right, bottom, alpha);
}
void CSprites::Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int xPivot, int yPivot)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, tex, xPivot, yPivot);
	sprites[id] = s;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, left, top, right, bottom);
}
void CSprites::Add(string id, LPSPRITE sprite)
{
	sprites[id] = sprite;
}
LPSPRITE CSprites::Get(string id)
{
	return sprites[id];
}

/*
	Clear all loaded textures
*/
void CSprites::Clear()
{
	for (auto x : sprites)
	{
		LPSPRITE s = x.second;
		delete s;
	}

	sprites.clear();
}



