#include "Grid.h"
#include "Game.h"

Grid::Grid(int col, int row, int cellWidth, int cellHeight)
{

	this->col = col+1;
	this->row = row+1;
	this->cellHeight = cellHeight;
	this->cellWidth = cellWidth;

	for (int x = 0; x <= col+1; ++x)
	{
		vector<Cell*> column ;
		for (int y = 0; y <= row+1; ++y)
		{
			Cell* cell = new Cell(x, y);
			column.push_back(cell);
		
		}
		cells.push_back(column);
	}
	 activeCells = new vector<Cell*>();
	 activeList = new vector<LPGAMEOBJECT>();

}

Grid::~Grid()
{
	DebugOut(L"[DELETE GRID] \n");
	
	activeCells->clear();
	activeList->clear();

	for (int x = 0; x < cellWidth; ++x)
	{
		for (int y = 0; y < cellHeight; ++y)
			delete cells.at(x).at(y);
		cells.at(x).clear();
	}
	cells.clear();
	delete activeCells;
	delete activeList;
}

void Grid::Update(float l, float t, float r, float b)
{
	getActiveCell(l, t, r, b);
	
	activeList->clear();
	for (auto cell : *activeCells)
		for (auto obj : *cell->getCellObject())
		{
			if (obj->ActiveGameObject == true && obj->CallCell == false)
			{
				activeList->push_back(obj);
				obj->CallCell = true;
			}
					
		}
	for (auto obj : *activeList)
	{
		obj->CallCell = false;
	}
	
}
void Grid::AddObject(LPGAMEOBJECT object)
{
	Cell* cell = getCellbyObjPosition(object->x, object->y);
	cell->AddObject(object);
	
}

void Grid::AddObject(LPGAMEOBJECT object, int cellx, int celly)
{
	Cell* cell = cells[cellx][celly];
	cell->AddObject(object);
//	DebugOut(L"[ADD Cell] \n");
	DebugOut(L"			[ADD Cell] : %d , %d   \n", cellx, celly);
}

void Grid::RemoveObject(LPGAMEOBJECT obj)
{
	Cell* cell = getCellbyObjPosition(obj->x, obj->y);
	cell->RemoveObject(obj);
}

Cell* Grid::getCell(int x, int y)
{
	if (x < 0) x = 0;
	if (x >= col) x = col;

	if (y < 0) y = 0;
	if (y >= row) y = row;

	return cells[x][y];
}

Cell* Grid::getCellbyObjPosition(float x, float y)
{
	int cellX = (int)(x / CELL_WIDTH);
	int cellY = (int)(y / CELL_HEIGHT);

	return getCell(cellX, cellY);
}

vector<LPGAMEOBJECT>* Grid::getActiveGameObject()
{
	
	return activeList;
}

void Grid::getActiveCell(float l, float t, float r, float b)
{
	
	int startx = (int)(l / cellWidth);
	int endx = (int)(r / cellWidth);
	int starty = (int)(t / cellHeight);
	int endy = (int)(b / cellHeight);

	activeCells->clear();
	if (startx < 0) startx = 0;
	for (int x = startx; x <= endx; ++x)
	{
		
		for (int y = starty; y <= endy; ++y)
		{
			
			activeCells->push_back(cells[x][y]);
		
		}
	}
}