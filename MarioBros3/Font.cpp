#include "Font.h"

Font::Font()
{
	Space = 24;
}

void Font::LoadFont()
{
	this->data = new CSprites();
	CSprites* sprite = CSprites::GetInstance();
	

	for (char c = '0'; c <= '9'; ++c)
	{
		string s =""+ c;
		data->Add(prefix + c, sprite->Get(prefix + c));
	}
		
	for (char c = 'A'; c <= 'Z'; ++c)
	{
		string s = "" + c;
		data->Add(prefix + c, sprite->Get(prefix + c));
	}
}

LPSPRITE Font::GetChar(char c)
{
	return this->data->Get(prefix + c);
}

void Font::setXMLprefix(string prefix)
{
	this->prefix = prefix;
}

void Font::RenderText(string text, D3DXVECTOR2 p)
{
	//missing render for align
	for (int i = 0; i <= text.length() - 1; i++)
	{
		char c = text.at(i);

		if (c == ' ')
		{
			p.x += this->getSpace();
			continue;
		}

		LPSPRITE charsprite = this->GetChar(c);

		charsprite->Draw(p.x, p.y,FALSE);

		p.x += charsprite->GetSpriteWidth() - 3;
	}
}

void Font::setSpace(float x)
{
	this->Space = x;
}

float Font::getSpace()
{
	return this->Space;
}
