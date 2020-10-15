#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
	static CTextures * __instance;

	unordered_map<string, LPDIRECT3DTEXTURE9> textures;

public: 
	CTextures();
	void Add(string id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(string id);

	void Clear();
	static CTextures * GetInstance();
};