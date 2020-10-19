
#include "TileSet.h"
#include "Game.h"

CTileSet::CTileSet(TiXmlElement* data, string xmlPath)
{
	data->QueryIntAttribute("firstgid", &firstgid);
	data->QueryFloatAttribute("tilewidth", &sizex);
	data->QueryFloatAttribute("tileheight", &sizey);
	data->QueryIntAttribute("tilecount", &tileCount);
	data->QueryIntAttribute("columns", &columns);

	
	CTextures* textures = CTextures::GetInstance();
	TiXmlElement* imgDom = data->FirstChildElement("image");
	string imgPath = xmlPath + "\\" + imgDom->Attribute("source");
	textures->Add(imgPath, ToLPCWSTR(imgPath), D3DCOLOR_XRGB(255, 255, 255));

	texture = CTextures::GetInstance()->Get(imgPath);
	DebugOut(L"[Load Tile] CTileSet = : %d \n", firstgid);
	
	for (TiXmlElement* node = data->FirstChildElement("tile"); node != nullptr; node = node->NextSiblingElement("tile"))
	{
		int id = 0; node->QueryIntAttribute("id", &id);
		
		TiXmlElement* objects = node->FirstChildElement("objectgroup");
		for (TiXmlElement* object = data->FirstChildElement("tile"); object != nullptr; object = object->NextSiblingElement("tile")) {
			
			if (object != NULL ) {
				PRECT rect = new RECT();
				int left, top, right, bottom;
				object->QueryIntAttribute("x",&left);
				object->QueryIntAttribute("y", &top);
				object->QueryIntAttribute("width", &right);
				object->QueryIntAttribute("height", &bottom);
				rect->left = left;
				rect->top = top;
				rect->right = rect->right + rect->left;
				rect->bottom = rect->top + rect->bottom;

				this->blocks[id] = rect;
				
			}
		}
	}
}

int CTileSet::GetFirstGID()
{
	return firstgid;
}

PRECT CTileSet::GetBlockBoundingBox(int id)
{
	if (id < firstgid) return nullptr;
	if (blocks.find(id) == blocks.end()) return nullptr;
	return blocks[id];
}

void CTileSet::Draw(int gid, int x, int y)
{
	if (gid < firstgid) return;

	int left, top, right, bottom;
	top = ((gid - firstgid) / columns) * sizey;
	left = ((gid - firstgid) % columns) * sizex;
	bottom = top + sizey;
	right = left + sizex;
	CGame* game = CGame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom);
	//CGame::GetInstance()->Draw(x, y, texture, left, top, right, bottom, 255);
}

CTileSet::~CTileSet()
{
	if (texture) {
		delete texture;
	}
	texture = NULL;
}
