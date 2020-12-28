
#include "GameMap.h"
#include "Brick.h"
#include "Solid.h"
#include "Ghost.h"
#include "Brick.h"
#include "Goomba.h"
#include "Koopas.h"
#include "QuestionBlock.h"
#include "Coin.h"


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
	if (data->QueryIntAttribute("visible", &this->visible))
		this->visible = 1;

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
				if (!layer->visible) continue;
				int id = layer->GetTileID(i % width, j % height);
				if(this->GetTileSet(id))
					this->GetTileSet(id)->Draw(id, x, y);
			}
		}
	}
	
}
vector<LPGAMEOBJECT> CGameMap::MapOBJECTS(string filePath, string fileName)
{
	string fullPath = filePath + "/" + fileName;
	TiXmlDocument doc(fullPath.c_str());

	vector<LPGAMEOBJECT> obj;

	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		//shared_ptr<CGameMap> gameMap = shared_ptr<CGameMap>(new CGameMap());

		for (TiXmlElement* TMXObjectsgroup = root->FirstChildElement("objectgroup"); TMXObjectsgroup != NULL; TMXObjectsgroup = TMXObjectsgroup->NextSiblingElement("objectgroup"))
		{
			for (TiXmlElement* TMXObject = TMXObjectsgroup->FirstChildElement("object"); TMXObject != NULL; TMXObject = TMXObject->NextSiblingElement("object"))
			{

				float x, y, width, height;
				
				string name = TMXObjectsgroup->Attribute("name");
				if (name == "Solid")
				{


					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryFloatAttribute("width", &width);
					TMXObject->QueryFloatAttribute("height", &height);

					Solid* solid = new Solid(x, y, width, height);
					obj.push_back(solid);
					
				}
				else if (name == "Ghost")
				{

					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryFloatAttribute("width", &width);
					TMXObject->QueryFloatAttribute("height", &height);

					Ghost* ghost = new Ghost(x, y, width, height);

					obj.push_back(ghost);

					CKoopas* enemies = new CKoopas();
					enemies->SetPosition(x, y);
					obj.push_back(enemies);
				}
				 if (name == "Enemies")
				{
					string Enemiesname= TMXObject->Attribute("name");
					string Type = TMXObject->Attribute("type");
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					//if (Enemiesname == "goomba")
					//{
						CKoopas* ene = new CKoopas();
						ene->SetPosition(x , y-100);
						obj.push_back(ene);
					//}

					
				}
				else if (name == "Items")
				{
					

					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					Coin* coin = new Coin(x,y);
					
					obj.push_back(coin);

				}
				else if (name == "QuestionBlocks")
				{
					
					int quantity = 0;
					string blockname;

					blockname = TMXObject->Attribute("name");
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryIntAttribute("type", &quantity);

					QuestionBlock* questionblock = new QuestionBlock(x,y);

					if (blockname == "bleaf")
					{
						questionblock->SetItem(Item::RaccoonLeaf);
					}
					else if (blockname == "bcoin")
					{
						questionblock->SetItem(Item::Coin);
					}
					else if (blockname == "bmushroom")
					{
						questionblock->SetItem(Item::RaccoonLeaf);
					}
					questionblock->SetQuantity(quantity);
					
					obj.push_back(questionblock);
				}
				else if (name == "Bricks")
				{
				
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);

					Brick* brick = new Brick(x,y);
					
				
					obj.push_back(brick);	
				}
				
			}
		}
	}
	return obj;
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