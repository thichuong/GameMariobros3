#pragma once
#include <unordered_map>
#include "Utils.h"
#include "TileSet.h"
#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"
#include "Game.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "CollisionBox.h"
using namespace std;

class CLayer
{
	

	int** tiles;

	//int tiles[500][500];
public:
	int id;

	int width;
	int height;
	CLayer();
	CLayer(TiXmlElement* data);

	bool Hidden = false;

	int GetTileID(int x, int y);

	~CLayer();
};

typedef CLayer* Layer;

class CGameMap
{
	int width;
	int height;
	int tileWidth;
	int tileHeight;

	vector< Layer> layers;
	unordered_map<int, TileSet> tilesets;
public:
	CGameMap();
	void Render(CGame* game);
	void FromTMX(string filePath, string fileName);
	vector<LPGAMEOBJECT> MapOBJECTS(string filePath, string fileName);
	TileSet GetTileSet(int id);
	~CGameMap();

};
  
LPGAMEOBJECT CreatObject(PRECT Box, int x, int y, CAnimations* Ani);