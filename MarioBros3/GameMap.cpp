
#include "GameMap.h"
#include "Brick.h"
#include "Solid.h"
#include "Ghost.h"
#include "Brick.h"
#include "Goomba.h"
#include "Koopas.h"
#include "RedKoopas.h"
#include "Redvenus.h"
#include "GreenVenus.h"
#include "Piranha.h"
#include "Paratroopa.h"
#include "RedGoomba.h"
#include "QuestionBlock.h"
#include "Coin.h"
#include "ItemBrick.h"
#include "WarpPipe.h"
#include "WarpMark.h"
#include "Reward.h"
#include "CTree.h"
#include "CNode.h"
#include "Portal.h"
#include "Platform.h"
#include "RedParatroopa.h"
#include "BoomerangBrother.h"


CLayer::CLayer()
{
	this->id = 0;
	this->width = 1;
	this->height = 1;
	this->visible = 1;
	tiles = new int* [1];
}

//,  = 44
CLayer::CLayer(TiXmlElement* data)
{
	data->QueryIntAttribute("id", &this->id);
	data->QueryIntAttribute("width", &this->width);
	data->QueryIntAttribute("height", &this->height);
	if (data->QueryIntAttribute("visible", &this->visible))
		this->visible = 1;
	Layername = data->Attribute("name");
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
	int Width = (int)game->GetScamX() / tileWidth;
	int Height = (int)game->GetScamY() / tileHeight;

	if (Width > 0) Width--;
	if (Height > 0) Height--;

	//Vec2 camSize = Vec2(this->camera->GetCamSize().x / tileWidth, this->camera->GetCamSize().y / tileHeight);

	int camWidth = (int)game->GetScreenWidth() / tileWidth;
	int camHeight = (int)game->GetScreenHeight() / tileHeight;
	for (int i = Width; i < camWidth + Width + 3; i++) {
		for (int j = Height; j < camHeight + Height + 3; j++) {
			int x = i * tileWidth;
			int y = j * tileHeight;
			for (Layer layer : layers) {
				if (!layer->visible) continue;
				int id = layer->GetTileID(i % width, j % height);
				if (this->GetTileSet(id))
					this->GetTileSet(id)->Draw(id, x, y);
			}
		}
	}

}
void  CGameMap::ReRender(CGame* game)
{
	int Width = (int)game->GetScamX() / tileWidth;
	int Height = (int)game->GetScamY() / tileHeight;

	if (Width > 0) Width--;
	if (Height > 0) Height--;

	//Vec2 camSize = Vec2(this->camera->GetCamSize().x / tileWidth, this->camera->GetCamSize().y / tileHeight);

	int camWidth = (int)game->GetScreenWidth() / tileWidth;
	int camHeight = (int)game->GetScreenHeight() / tileHeight;
	for (int i = Width; i < camWidth + Width + 3; i++) {
		for (int j = Height; j < camHeight + Height + 3; j++) {
			int x = i * tileWidth;
			int y = j * tileHeight;
			for (Layer layer : layers) {
				if (layer->Layername == "Foreground")
				{
					int id = layer->GetTileID(i % width, j % height);
					if (this->GetTileSet(id))
						this->GetTileSet(id)->Draw(id, x, y);
				}
			}
		}
	}
}
void CGameMap::MapOBJECTS(string filePath, string fileName)
{
	string fullPath = filePath + "/" + fileName;
	TiXmlDocument doc(fullPath.c_str());



	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		//shared_ptr<CGameMap> gameMap = shared_ptr<CGameMap>(new CGameMap());

		for (TiXmlElement* TMXObjectsgroup = root->FirstChildElement("objectgroup"); TMXObjectsgroup != NULL; TMXObjectsgroup = TMXObjectsgroup->NextSiblingElement("objectgroup"))
		{
			string name = TMXObjectsgroup->Attribute("name");
			for (TiXmlElement* TMXObject = TMXObjectsgroup->FirstChildElement("object"); TMXObject != NULL; TMXObject = TMXObject->NextSiblingElement("object"))
			{

				float x, y, width, height;


				if (name == "Solid")
				{
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryFloatAttribute("width", &width);
					TMXObject->QueryFloatAttribute("height", &height);

					Solid* solid = new Solid(x, y, width, height);
					//CGame::GetInstance()->GetCurrentScene()->newObject(solid);
					
					TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
					for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
					{
						string nameGrid = node->Attribute("name");
						if (nameGrid == "Grid")
						{
							string Gird = node->Attribute("value");
							CGame::GetInstance()->GetCurrentScene()->newObject(solid, Gird);
						}
						
					}

				}
				else if (name == "Ghost")
				{
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryFloatAttribute("width", &width);
					TMXObject->QueryFloatAttribute("height", &height);

					Ghost* ghost = new Ghost(x, y, width, height);

					TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
					for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
					{
						string nameGrid = node->Attribute("name");
						if (nameGrid == "Grid")
						{
							string Gird = node->Attribute("value");
							CGame::GetInstance()->GetCurrentScene()->newObject(ghost, Gird);
						}

					}

				}
				else if (name == "Enemy")
				{
					string Enemiesname = TMXObject->Attribute("name");
					string Type = TMXObject->Attribute("type");
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					if (Enemiesname == "goomba")
					{
						CGoomba* enemies = new CGoomba();
						enemies->SetAnimationSet(CAnimations::GetInstance());
						enemies->SetPosition(x, y);
						CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
					}
					if (Enemiesname == "para-goomba")
					{
						RedGoomba* enemies = new RedGoomba();
						enemies->SetAnimationSet(CAnimations::GetInstance());
						enemies->SetPosition(x, y);
						CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
					}
					if (Enemiesname == "koopa")
					{
						if (Type == "green")
						{
							CKoopas* enemies = new CKoopas();
							enemies->SetAnimationSet(CAnimations::GetInstance());
							enemies->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
						}
						if (Type == "red")
						{
							RedKoopas* enemies = new RedKoopas();
							enemies->SetAnimationSet(CAnimations::GetInstance());
							enemies->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
						}
						if (Type == "green-para")
						{
							Paratroopa* enemies = new Paratroopa();
							enemies->SetAnimationSet(CAnimations::GetInstance());
							enemies->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
						}
						if (Type == "red-para")
						{
							RedParatroopa* enemies = new RedParatroopa();
							enemies->SetAnimationSet(CAnimations::GetInstance());
							enemies->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
						}

					}
					if (Enemiesname == "venus")
					{

						if (Type == "red")
						{
							Redvenus* enemies = new Redvenus();
							enemies->SetAnimationSet(CAnimations::GetInstance());
							enemies->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
						}
						if (Type == "green")
						{
							GreenVenus* enemies = new GreenVenus();
							enemies->SetAnimationSet(CAnimations::GetInstance());
							enemies->SetPosition(x, y);
							CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
						}


					}
					if (Enemiesname == "piranha")
					{
						Piranha* enemies = new Piranha();
						enemies->SetAnimationSet(CAnimations::GetInstance());
						enemies->SetPosition(x, y);
						CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
					}
					if (Enemiesname == "boomerang-brother")
					{
						BoomerangBrother* enemies = new BoomerangBrother();
						enemies->SetAnimationSet(CAnimations::GetInstance());
						enemies->SetPosition(x, y);
						CGame::GetInstance()->GetCurrentScene()->newObject(enemies);
					}

				}
				else if (name == "Coin")
				{


					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					Coin* coin = new Coin(x, y);
					//CGame::GetInstance()->GetCurrentScene()->newObject(coin);

					TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
					for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
					{
						string nameGrid = node->Attribute("name");
						if (nameGrid == "Grid")
						{
							string Gird = node->Attribute("value");
							CGame::GetInstance()->GetCurrentScene()->newObject(coin, Gird);
						}

					}
					

				}
				else if (name == "QuestionBlocks")
				{

					int quantity = 0;
					string blockname;

					blockname = TMXObject->Attribute("name");
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryIntAttribute("type", &quantity);

					QuestionBlock* questionblock = new QuestionBlock(x, y);

					if (blockname == "bleaf")
					{
						questionblock->SetItem(Item::Leaf);
					}
					else if (blockname == "bcoin")
					{
						questionblock->SetItem(Item::Coin);
					}
					else if (blockname == "bmushroom")
					{
						questionblock->SetItem(Item::Leaf);
					}
					else if (blockname == "f1up-mushroom")
					{
						questionblock->SetItem(Item::UPRoom);
					}

					questionblock->quantity = quantity;
					DebugOut(L"[questionblock ] quantity = %d \n", questionblock->quantity);


					TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
					for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
					{
						string nameGrid = node->Attribute("name");
						if (nameGrid == "Grid")
						{
							string Gird = node->Attribute("value");
							CGame::GetInstance()->GetCurrentScene()->newObject(questionblock, Gird);
						}

					}


				}
				else if (name == "Brick")
				{

					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);

					if (TMXObject->Attribute("name") == NULL)
					{
						Brick* brick = new Brick(x, y);
						//CGame::GetInstance()->GetCurrentScene()->newObject(brick);
						TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
						for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
						{
							string nameGrid = node->Attribute("name");
							if (nameGrid == "Grid")
							{
								string Gird = node->Attribute("value");
								CGame::GetInstance()->GetCurrentScene()->newObject(brick, Gird);
							}

						}
					}
					else
					{
						string name;
						name = TMXObject->Attribute("name");
						int type;  
						TMXObject->QueryIntAttribute("type", &type);
						ItemBrick* brick = new ItemBrick();
						brick->SetPosition(x, y);
						brick->quantity = type;
						if (name == "p-switch")
						{
							brick->SetItem(Item::PSwitch);
						}
						if (name == "bleaf")
						{
							brick->SetItem(Item::Leaf);
						}
						else if (name == "bcoin")
						{
							brick->SetItem(Item::Coin);
						}
						else if (name == "bmushroom")
						{
							brick->SetItem(Item::Leaf);
						}
						else if (name == "f1up-mushroom")
						{
							brick->SetItem(Item::UPRoom);
						}
						TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
						for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
						{
							string nameGrid = node->Attribute("name");
							if (nameGrid == "Grid")
							{
								string Gird = node->Attribute("value");
								CGame::GetInstance()->GetCurrentScene()->newObject(brick, Gird);
								//DebugOut(L"[ADD Cell] \n");
							}

						}
					}
				}
				else if (name == "Warp")
				{

					string Warpname;

					Warpname = TMXObject->Attribute("name");
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryFloatAttribute("width", &width);
					TMXObject->QueryFloatAttribute("height", &height);

					if (Warpname == "warp-pipe")
					{
						string typeWarp = TMXObject->Attribute("type");
						WarpPipe* warppipe = new WarpPipe(x, y, width, height);
						if (typeWarp == "down")
						{
							warppipe->setWarp(TypeWarp::down);
						}
						if (typeWarp == "up")
						{
							warppipe->setWarp(TypeWarp::up);
						}
						// DebugOut(L"[warp-pipe] = %f \n", 1);
						CGame::GetInstance()->GetCurrentScene()->newObject(warppipe);
					}
					if (Warpname == "warp-mark")
					{
						WarpMark* warpmark = new WarpMark(x, y, width, height);
						string markname;
						int cameraid = 0;
						string typeWarp;
						float destx = 0;
						float desty = 0;
						int block;
						TiXmlElement* props = TMXObject->FirstChildElement("properties");
						for (TiXmlElement* node = props->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
						{
							markname = node->Attribute("name");

							if (markname == "camera-bound-id") node->QueryIntAttribute("value", &cameraid);
							if (markname == "dest-x")	node->QueryFloatAttribute("value", &destx);
							if (markname == "dest-y")	node->QueryFloatAttribute("value", &desty);
							if (markname == "lock")
							{
								// node->QueryIntAttribute("value", &block);
								 //if (block == 1) warpmark->Block();
								// else warpmark->UnBlock();
							}
							if (markname == "out-direction")
							{
								typeWarp = node->Attribute("value");

							}

							// DebugOut(L"[warp-mark] = %f \n", 1);
						}
						warpmark->set(cameraid, destx, desty);
						if (typeWarp == "down")
						{
							warpmark->setWarp(TypeWarp::down);
						}
						if (typeWarp == "up")
						{
							warpmark->setWarp(TypeWarp::up);
						}
						// DebugOut(L"[warp-mark] = %f \n", 1);

						TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
						for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
						{
							string nameGrid = node->Attribute("name");
							if (nameGrid == "Grid")
							{
								string Gird = node->Attribute("value");
								CGame::GetInstance()->GetCurrentScene()->newObject(warpmark, Gird);
							}

						}
						//CGame::GetInstance()->GetCurrentScene()->newObject(warpmark);
					}

				}
				else if (name == "Card")
				{
					string Cardname;

					Cardname = TMXObject->Attribute("name");
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					if (Cardname == "reward")
					{
						Reward* reward = new Reward(x, y);
						//CGame::GetInstance()->GetCurrentScene()->newObject(reward);

						TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
						for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
						{
							string nameGrid = node->Attribute("name");
							if (nameGrid == "Grid")
							{
								string Gird = node->Attribute("value");
								CGame::GetInstance()->GetCurrentScene()->newObject(reward, Gird);
							}

						}
					}

				}
				else if (name == "AnimatedBG")
				{

					CTree* tree = new CTree();
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);

					tree->SetPosition(x, y);
					CGame::GetInstance()->GetCurrentScene()->newObject(tree);

				}
				else if (name == "WorldGraph")
				{
					CNode* cnode = new CNode();
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					cnode->SetPosition(x, y);
					string typeNode = "";
					string nameproperty = "";
					if (TMXObject->Attribute("type"))
					{
						typeNode = TMXObject->Attribute("type");
						cnode->SetTypeNode(typeNode);
					}
					else
					{
						//typeNode = TMXObject->Attribute("type");
						cnode->SetTypeNode(typeNode);
					}
					TiXmlElement* props = TMXObject->FirstChildElement("properties");
					for (TiXmlElement* node = props->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
					{
						nameproperty = node->Attribute("name");

						if (nameproperty == "adjacent_weight")
						{
							vector<string> adjacent_weight = split(node->Attribute("value"), ",");
							for (int i = 0; i < adjacent_weight.size(); i++)
							{
								if (adjacent_weight[i] == "l") cnode->left = true;
								else if (adjacent_weight[i] == "r") cnode->right = true;
								else if (adjacent_weight[i] == "u") cnode->up = true;
								else if (adjacent_weight[i] == "d") cnode->down = true;
							}

						}
						if (nameproperty == "scene")
						{

							int idscene = 0;
							node->QueryIntAttribute("value", &idscene);
							DebugOut(L"[NODE_MAP] sceneID = %d \n", idscene);
							cnode->SetIDscene(idscene);


						}
						if (nameproperty == "node_id")
						{
							if (node->Attribute("value") != "")
							{
								int idNode = 0;
								node->QueryIntAttribute("value", &idNode);
								cnode->SetNodeID(idNode);
							}
						}

					}

					CGame::GetInstance()->GetCurrentScene()->newObject(cnode);
				}
				else if (name == "Portal")
				{
					int idSCence = 0;
					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);
					TMXObject->QueryFloatAttribute("width", &width);
					TMXObject->QueryFloatAttribute("height", &height);

					TMXObject->QueryIntAttribute("type", &idSCence);
					CPortal* Portal = new CPortal(x, y, width, height, idSCence);
					CGame::GetInstance()->GetCurrentScene()->newObject(Portal);
				}
				else if (name == "MovingPlatforms")
				{

					TMXObject->QueryFloatAttribute("x", &x);
					TMXObject->QueryFloatAttribute("y", &y);


					Platform* platform = new Platform();
					platform->SetPosition(x, y);

					TiXmlElement* props = TMXObject->FirstChildElement("properties");
					for (TiXmlElement* node = props->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
					{
						float vx = 0, vy = 0;
						string property_name = node->Attribute("name");
						if (property_name == "VelocityX")
						{
							node->QueryFloatAttribute("value", &vx);
							platform->SetSpeed(vx, 0.0f);

						}
						if (property_name == "VelocityY") node->QueryFloatAttribute("value", &vy);



					}
					TiXmlElement* TMX = TMXObject->FirstChildElement("properties");
					for (TiXmlElement* node = TMX->FirstChildElement("property"); node != nullptr; node = node->NextSiblingElement("property"))
					{
						string nameGrid = node->Attribute("name");
						if (nameGrid == "Grid")
						{
							string Gird = node->Attribute("value");
							CGame::GetInstance()->GetCurrentScene()->newObject(platform, Gird);
						}

					}
					//CGame::GetInstance()->GetCurrentScene()->newObject(platform);
				}
			}
		}
	}

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
