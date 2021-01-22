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

	int x, y;

	vector<LPGAMEOBJECT>* objects;

	int width, height;
public:
	Cell(int x, int y);
	~Cell();

	int getX();
	int getY();

	void AddObject(CGameObject* obj);
	void RemoveObject(CGameObject* obj);

	vector<LPGAMEOBJECT>* getCellObject();
};

