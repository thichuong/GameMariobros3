#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <string>
using namespace std;

class CSprite
{
	string id;				// Sprite ID in the sprite database

	int xPivot;
	int left; 
	int top;
	int right;
	int bottom;

	LPDIRECT3DTEXTURE9 texture;
public: 
	CSprite(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex,int xPivot =0);

	void Draw(float x, float y, bool fliplex, int alpha = 255);
	void Draw(float x, float y, D3DXVECTOR2 vectorflip, int alpha = 255);
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<string, LPSPRITE> sprites;

public:
	void Add(string id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex, int xPivot = 0);
	LPSPRITE Get(string id);
	void Clear();

	static CSprites * GetInstance();
};



