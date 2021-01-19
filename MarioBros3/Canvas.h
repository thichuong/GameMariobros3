#pragma once

#include "Font.h"
#include "Sprites.h"

class Canvas 
{
protected:
	Font* font;
	D3DXVECTOR2 position;
public:
	Canvas();
	~Canvas();
	void setPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 getPosition();
	virtual void Update(DWORD dt);
	virtual void Render();
};

