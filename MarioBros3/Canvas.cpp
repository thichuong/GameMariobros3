#include "Canvas.h"

Canvas::Canvas()
{
	font = new Font();
	position = D3DXVECTOR2(0, 0);
	font->LoadFont();
}

Canvas::~Canvas()
{

}

D3DXVECTOR2 Canvas::getPosition()
{
	return  position;
}

void Canvas::setPosition(D3DXVECTOR2 position)
{
	this->position = position;
}
void Canvas::Update(DWORD dt)
{

}
void Canvas::Render()
{

}