#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;

	width = CELL_WIDTH;
	height = CELL_HEIGHT;
	objects = new unordered_set<LPGAMEOBJECT>();

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
		
	if (objects->find(obj) == objects->end())
		objects->insert(obj);
}

void Cell::RemoveObject(CGameObject* obj)
{
	if (objects->find(obj) != objects->end())
		objects->erase(obj);
}

unordered_set<LPGAMEOBJECT>* Cell::getCellObject()
{
	return this->objects;
}
