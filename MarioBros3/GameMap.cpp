
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
	DebugOut(L"[Load Layer] CTileSet = : %d \n", id);
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
	for (auto& tileset : tilesets) 
	{
			if (id >= tileset.second->GetFirstGID() && id <= tileset.second->GettileCount())
				return tileset.second;
	}
	return NULL;
}
void CGameMap::Render(CGame* game)
{
	int Width = game->GetScamX() / tileWidth;
	int Height = game->GetScamY() / tileHeight;

	if (Width > 0) Width--;
	if (Height > 0) Height--;

	//Vec2 camSize = Vec2(this->camera->GetCamSize().x / tileWidth, this->camera->GetCamSize().y / tileHeight);
	
	int camWidth = game->GetScreenWidth() / tileWidth;
	int camHeight = game->GetScreenHeight() / tileHeight;
	for (int i = Width; i < camWidth + Width + 3; i++) {
		for (int j = Height; j < camHeight + Height + 3; j++) {
			int x = i * tileWidth ;
			int y = j * tileHeight ;
			for (Layer layer : layers) {
				if (layer->Hidden) continue;
				int id = layer->GetTileID(i % width, j % height);
				if(this->GetTileSet(id))
					this->GetTileSet(id)->Draw(id, x, y);
			}
		}
	}
	
}
vector<LPGAMEOBJECT> CGameMap::MapOBJECTS( CAnimations* PlayAni)
{
	vector<LPGAMEOBJECT> objects;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height ; j++) {
			int x = i * tileWidth;
			int y = j * tileHeight;
			for (Layer layer : layers) {
				
					int id = layer->GetTileID(i % width, j % height);
					if(this->GetTileSet(id))
						if(this->GetTileSet(id)->GetBlockBoundingBox(id))
							objects.push_back(CreatObject(this->GetTileSet(id)->GetBlockBoundingBox(id), x, y, PlayAni));
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
			TileSet tileSet = new CTileSet(node, filePath);
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
LPGAMEOBJECT CreatObject(PRECT Box, int x, int y, CAnimations* Ani)
{
	CGameObject* obj = NULL;
	if(Box !=NULL)
	{
		obj = new CCollisionBox(Box->left, Box->top, Box->right, Box->bottom);
		obj->SetPosition(x, y);
		obj->SetAnimationSet(Ani);
		DebugOut(L"		[Load BOX] CTileSet = : %d \n", Box->bottom);
	}
	return obj;
}