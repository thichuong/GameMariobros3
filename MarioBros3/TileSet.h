#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Utils.h"
#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"

 
class CTileSet
{
	int firstgid;

	int tileCount;
	int columns;
	float sizex;
	float sizey;
	//RECT r;
	LPDIRECT3DTEXTURE9 texture;

	unordered_map<int, PRECT> blocks;

public:
	
	CTileSet(TiXmlElement* data, string xmlPath);

	int GetFirstGID();
	int GettileCount() { return tileCount; };
	PRECT GetBlockBoundingBox(int id);

	void Draw(int gid, int x, int y);

	~CTileSet();

};
typedef CTileSet* TileSet;