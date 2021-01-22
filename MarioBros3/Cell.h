#pragma once
#include "GameObject.h"
#include <unordered_set>

#define CELL_WIDTH 385
#define CELL_HEIGHT 290

using namespace std;

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

class Cell
{
public:
	int x, y;

	unordered_set<LPGAMEOBJECT>* objects;

	int width, height;


	Cell(int x, int y);
	~Cell();

	int getX();
	int getY();

	void AddObject(CGameObject* obj);
	void RemoveObject(CGameObject* obj);

	unordered_set<LPGAMEOBJECT>* getCellObject();


};

