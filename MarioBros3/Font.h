#pragma once

#include "Sprites.h"

class Font
{
	string prefix;
	float Space;
	CSprites* data;
public:

	Font();

	//run this before import the font
	void LoadFont();

	//use this to get the desired character font; 
	LPSPRITE GetChar(char c);

	//use this to change prefix for font in XML, in this case spr-font-
	void setXMLprefix(std::string prefix);

	void RenderText(string text, D3DXVECTOR2 p);

	void setSpace(float x);

	float getSpace();
};

