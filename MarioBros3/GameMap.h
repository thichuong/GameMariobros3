#pragma once
#include <unordered_map>
#include "Utils.h"
#include "TileSet.h"
//#include "TinyXML/tinyxml.h"
//#include "TinyXML/tinystr.h"
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
	string Layername;
	int id;

	int width;
	int height;
	CLayer();
	CLayer(TiXmlElement* data);
	int visible;
	

	int GetTileID(int x, int y);

	~CLayer();
};

typedef CLayer* Layer;

class CGameMap
{
	int width = 0;
	int height =0;
	int tileWidth =0;
	int tileHeight =0;

	vector< Layer> layers;
	unordered_map<int, TileSet> tilesets;
public:
	CGameMap();
	void Render(CGame* game);
	void ReRender(CGame* game);
	void FromTMX(string filePath, string fileName);
	void MapOBJECTS(string filePath, string fileName);
	TileSet GetTileSet(int id);
	~CGameMap();

};
  
