
#include "GameMap.h"
CLayer::CLayer()
{
	this->id = 0;
	this->width = 1;
	this->height = 1;
}

//,  = 44
CLayer::CLayer(TiXmlElement* data)
{
	data->QueryIntAttribute("id", &this->id);
	data->QueryIntAttribute("width", &this->width);
	data->QueryIntAttribute("height", &this->height);

	tiles = new int* [this->width];
	const char* content = data->FirstChildElement()->GetText();
	vector<string> splitted = split(content, ",");
	for (int i = 0; i < this->width; i++) {
		tiles[i] = new int[height];
		for (int j = 0; j < this->height; j++) {
			tiles[i][j] = stoi(splitted[i + j * width]);
			
		}
	}

	splitted.clear();
}

int CLayer::GetTileID(int x, int y)
{
	return tiles[x][y];
}

CLayer::~CLayer()
{
	for (int i = 0; i < width; i++) {
		delete[] tiles[i];
	}
	delete[] tiles;
}
CGameMap::CGameMap()
{

}
TileSet CGameMap::GetTileSet(int id)
{
	TileSet tileset = tilesets[id];
	if (tileset == NULL)
		DebugOut(L"[ERROR] Failed to find animation id: %d\n", id);
	return tileset;
}
void CGameMap::Render(CGame* game)
{
	int col = game->GetScamX() / tileWidth;
	int row = game->GetScamY() / tileHeight;

	if (col > 0) col--;
	if (row > 0) row--;

	//Vec2 camSize = Vec2(this->camera->GetCamSize().x / tileWidth, this->camera->GetCamSize().y / tileHeight);
	
	int camsizex= game->GetScreenWidth() / tileWidth;
	int camsizey = game->GetScreenHeight() / tileHeight;
	for (int i = col; i < camsizex + col + 5; i++) {
		for (int j = row; j < camsizey + row + 5; j++) {
			int x = i * tileWidth ;
			int y = j * tileHeight ;
			for (Layer layer : layers) {
				if (layer->Hidden) continue;
				int id = layer->GetTileID(i % width, j % height);
				this->GetTileSet(1)->Draw(id, x, y);
			}
		}
	}
	
}
vector<LPGAMEOBJECT> CGameMap::MapOBJECTS( CAnimations* PlayAni)
{
	vector<LPGAMEOBJECT> objects;
	DebugOut(L"[Load] obj %d\n", 2);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height ; j++) {
			int x = i * tileWidth;
			int y = j * tileHeight;
			for (Layer layer : layers) {
				
				int id = layer->GetTileID(i % width, j % height);
				DebugOut(L"	[Load] obj %d\n", id);
				if(CreatObject(id, x, y, PlayAni))
					objects.push_back(CreatObject(id, x, y, PlayAni));
			}
		}
	}
	return objects;
}

void CGameMap::FromTMX(string filePath, string fileName)
{
	string fullPath = filePath + "/" + fileName;
	TiXmlDocument doc(fullPath.c_str());

	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		//shared_ptr<CGameMap> gameMap = shared_ptr<CGameMap>(new CGameMap());

		root->QueryIntAttribute("width", &width);
		root->QueryIntAttribute("height", &height);
		root->QueryIntAttribute("tilewidth", &tileWidth);
		root->QueryIntAttribute("tileheight", &tileHeight);

		//Load tileset
		for (TiXmlElement* node = root->FirstChildElement("tileset"); node != nullptr; node = node->NextSiblingElement("tileset")) {
			TileSet tileSet = new CTileSet(node, "Textures\\Maps");
			tilesets[tileSet->GetFirstGID()] = tileSet;
		}

		//Load layer
		for (TiXmlElement* node = root->FirstChildElement("layer"); node != nullptr; node = node->NextSiblingElement("layer")) {
			Layer layer = new CLayer(node);
			this->layers.push_back(layer);
		}
	}

	//throw "Load map that bai!!";
}

CGameMap::~CGameMap()
{
	layers.clear();
	tilesets.clear();
}
LPGAMEOBJECT CreatObject(int id, int x, int y, CAnimations* Ani)
{
	CGameObject* obj = NULL;
	DebugOut(L"		[New] obj %d\n", id);
	switch (id)
	{
	case 391:
	case 392:
	case 490:
	case 491:
	case 520:
	case 521:
		obj = new CBrick();
		obj->SetPosition(x, y);
		obj->SetAnimationSet(Ani);
		
		break;
	default:
		break;
	}
	return obj;
}