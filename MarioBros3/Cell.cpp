#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;

	width = CELL_WIDTH;
	height = CELL_HEIGHT;
	objects =new  vector<CGameObject*>();
}

Cell::~Cell()
{
}

int Cell::getX()
{
	return this->x;
}

int Cell::getY()
{
	return this->y;
}

void Cell::AddObject(CGameObject* obj)
{	
	if( !(find(objects->begin(), objects->end(), obj) != objects->end()))
	{
		objects->push_back(obj);
	}
}

void Cell::RemoveObject(CGameObject* obj)
{
	for (size_t i = 0; i < objects->size(); i++)
	{
		if (objects->at(i) == obj) objects->erase(objects->begin() + i);
	}
	
}

vector<LPGAMEOBJECT>* Cell::getCellObject()
{
	return objects;
}
