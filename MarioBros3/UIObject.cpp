#include "UIObject.h"

UIObject::UIObject()
{
	this->Position =D3DXVECTOR2(0,0);
}

UIObject::~UIObject()
{
	animation_set.clear();
}

void UIObject::setPosition(D3DXVECTOR2 position)
{
	this->Position = position; 
}

D3DXVECTOR2 UIObject::getPosition()
{
	return this->Position; 
}

void UIObject::AddAnimation(std::string name, LPANIMATION animation)
{
	animation_set[name] = animation;
}

void UIObject::Update(DWORD dt)
{
	this->dt = dt; 
}

void UIObject::Render()
{

}
