#include "UIObject.h"

UIObject::UIObject()
{
	this->StaticPosition = D3DXVECTOR2(0,0);
}

UIObject::~UIObject()
{
	animation_set.clear();
}

void UIObject::setStaticPosition(D3DXVECTOR2 position)
{
	this->StaticPosition = position; 
}

D3DXVECTOR2 UIObject::getStaticPosition()
{
	return this->StaticPosition; 
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
