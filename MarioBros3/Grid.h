#pragma once
#include "Cell.h"


class Grid
{
	int col;
	int row;
	int cellWidth;
	int cellHeight;
	vector<vector<Cell*>> Cells;
	vector <Cell*>* activecells;
	vector<LPGAMEOBJECT>* activeObject;
public:
	Grid(int col, int row, int cellWidth, int cellHeight);
	~Grid();
	void Update(float l, float t, float r, float b);

	void AddObject(LPGAMEOBJECT object);

	void AddObject(LPGAMEOBJECT object, int cellx, int celly);

	void RemoveObject(LPGAMEOBJECT obj);

	//use this to get specific cell in grid
	Cell* getCell(int x, int y);

	Cell* getCellbyObjPosition(float x, float y);

	vector<LPGAMEOBJECT>* getActiveGameObject();

	void getActiveCell(float l, float t, float r, float b);

};

