#include "Grid.h"
#include "Game.h"

Grid::Grid(int col, int row, int cellWidth, int cellHeight)
{
	
	activecells = new vector<Cell*>();
	activeObject = new std::vector<LPGAMEOBJECT>();

	this->col = col;
	this->row = row;
	this->cellHeight = cellHeight;
	this->cellWidth = cellWidth;

	for (int x = 0; x < col; ++x)
	{
		vector<Cell*> column;
		for (int y = 0; y < row; ++y)
		{
			Cell* cell = new Cell(x, y);
			column.push_back(cell);
		}
		Cells.push_back(column);
	}


}

Grid::~Grid()
{
	for (int x = 0; x < col; ++x)
	{
		for (int y = 0; y < row; ++y)
			delete Cells.at(x).at(y);
		Cells.at(x).clear();
	}
	Cells.clear();
}

void Grid::Update(float l, float t, float r, float b)
{
	getActiveCell(l, t, r, b);

}
void Grid::AddObject(LPGAMEOBJECT object)
{
	Cell* cell = getCellbyObjPosition(object->x, object->y);
	cell->AddObject(object);
	
}

void Grid::AddObject(LPGAMEOBJECT object, int cellx, int celly)
{
	Cell* cell = Cells[cellx][celly];
	cell->AddObject(object);
	//DebugOut(L"[ADD Cell] \n");
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

	return Cells[x][y];
}

Cell* Grid::getCellbyObjPosition(float x, float y)
{
	int cellX = (int)(x / CELL_WIDTH);
	int cellY = (int)(y / CELL_HEIGHT);

	return getCell(cellX, cellY);
}

vector<LPGAMEOBJECT>* Grid::getActiveGameObject()
{

	unordered_set<LPGAMEOBJECT > coObject;
	coObject.clear();
	for (auto cell = activecells->begin(); cell != activecells->end(); ++cell)
		for (auto o : *((*cell)->objects))
		{
			coObject.insert(o);
			//o->CallCell = false;
		}
	activeObject->clear();
	for (auto obj : coObject)
	{
		//if (obj->CallCell == false)
		//{
			activeObject->push_back(obj);
		//	obj->CallCell = true;
		//}
	}

	return activeObject;
}

void Grid::getActiveCell(float l, float t, float r, float b)
{
	activecells->clear();
	int startX = (int)(l / cellWidth);
	int endX = (int)(r / cellWidth);
	int startY = (int)(t / cellHeight);
	int endY = (int)(b / cellHeight);

	for (int i = startX; i <= endX; ++i)
	{
		if (i < 0 || i >= col) continue;

		for (int j = startY; j <= endY; ++j)
		{
			if (j<0 || j > row) continue;

			activecells->push_back(Cells[i][j]);
		}
	}
}