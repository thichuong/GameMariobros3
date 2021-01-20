#include "MapScene.h"


MapScene::MapScene(int id, string filePath) :
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);

	gamemap = NULL;
	canvas = NULL;
	hud = new HUD();
}

void MapScene::_ParseSection_SPRITES(string line)
{

	TiXmlDocument doc(line.c_str());

	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		//	TiXmlElement* texture = root->FirstChildElement();
		for (TiXmlElement* texture = root->FirstChildElement("Textures"); texture != NULL; texture = texture->NextSiblingElement("Textures"))
		{
			string textureID = texture->Attribute("id");
			LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(textureID);

			for (TiXmlElement* node = texture->FirstChildElement(); node != nullptr; node = node->NextSiblingElement())
			{
				string spriteID = node->Attribute("id");
				int left, top, width, height;
				int xPivot = 0;
				int yPivot = 0;
				node->QueryIntAttribute("left", &left);
				node->QueryIntAttribute("top", &top);
				node->QueryIntAttribute("width", &width);
				node->QueryIntAttribute("height", &height);
				if (node->Attribute("xPivot") != NULL) node->QueryIntAttribute("xPivot", &xPivot);
				if (node->Attribute("yPivot") != NULL) node->QueryIntAttribute("yPivot", &yPivot);
				left = left * 3;
				top = top * 3;
				width = width * 3;
				height = height * 3;

				CSprites::GetInstance()->Add(spriteID, left, top, left + width, top + height, tex, xPivot, yPivot);
			}
		}
	}
	//DebugOut(L"[INFO] Loading aniId = : %s \n", ToLPCWSTR(line));
}
void MapScene::_ParseSection_ANIMATIONS(string line)
{

	TiXmlDocument doc(line.c_str());

	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		for (TiXmlElement* texture = root->FirstChildElement("Textures"); texture != NULL; texture = texture->NextSiblingElement("Textures"))
		{


			string gameObjectID = texture->Attribute("gameObjectId");
			string textureID = texture->Attribute("textureId");
			//DebugOut(L"	[Amni] = : %s \n", ToLPCWSTR(textureID));


			for (TiXmlElement* node = texture->FirstChildElement(); node != nullptr; node = node->NextSiblingElement())
			{
				string aniId = node->Attribute("aniId");
				float frameTime;
				node->QueryFloatAttribute("frameTime", &frameTime);
				//string name = node->Attribute("id");

				LPANIMATION ani = new CAnimation(frameTime);
				//DebugOut(L"[INFO] Loading aniId = : %s \n", ToLPCWSTR(aniId));
				for (TiXmlElement* sprNode = node->FirstChildElement(); sprNode != nullptr; sprNode = sprNode->NextSiblingElement())
				{
					string id = sprNode->Attribute("id");
					LPSPRITE sprite = CSprites::GetInstance()->Get(id);
					ani->Add(sprite, frameTime);
					//DebugOut(L"					 Loading Id = : %s \n", ToLPCWSTR(id));
				}

				CAnimations::GetInstance()->Add(aniId, ani);


			}
		}
	}
}
void MapScene::Load()
{
	//LoadSource();
	/*playsprites = csprites::getinstance();
	playani = canimations::getinstance();*/

	TiXmlDocument doc(sceneFilePath.c_str());
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* info = root->FirstChildElement();
		string Name = info->Attribute("Game");
		int id;
		info->QueryIntAttribute("id", &id);
		TiXmlElement* node = info->FirstChildElement("LoadMAP");
		string file = node->Attribute("file");
		string filepath = node->Attribute("filepath");
		DebugOut(L"[INFO] GameMap: %s \n", file.c_str());


		for (TiXmlElement* node = info->FirstChildElement("LoadSPRITES"); node != nullptr; node = node->NextSiblingElement("LoadSPRITES"))
		{
			string file = node->Attribute("file");
			string source = node->Attribute("source");
			string textureId = node->Attribute("textureId");
			CTextures* textures = CTextures::GetInstance();
			int a;
			if (node->QueryIntAttribute("a", &a))
			{
				textures->Add(textureId, ToLPCWSTR(source), D3DCOLOR_ARGB(0, 255, 255, 255));
			}
			else
			{
				node->QueryIntAttribute("a", &a);
				textures->Add(textureId, ToLPCWSTR(source), D3DCOLOR_ARGB(a, 255, 255, 255));
			}

			//_ParseSection_SPRITES("file");
			DebugOut(L"[INFO]Start load : %d \n", id);
			_ParseSection_SPRITES(file);

		}
		for (TiXmlElement* node = info->FirstChildElement("LoadANIMATIONS"); node != nullptr; node = node->NextSiblingElement("LoadANIMATIONS"))
		{
			string file = node->Attribute("file");
			_ParseSection_ANIMATIONS(file);
		}

		for (TiXmlElement* node = info->FirstChildElement("Camera"); node != nullptr; node = node->NextSiblingElement("Camera"))
		{
			int start;
			node->QueryIntAttribute("start", &start);
			for (TiXmlElement* detail = node->FirstChildElement("Boundary"); detail != nullptr; detail = detail->NextSiblingElement("Boundary"))
			{
				int id;
				float pos_x, pos_y, left, top, right, bottom;
				detail->QueryIntAttribute("id", &id);
				detail->QueryFloatAttribute("pos_x", &pos_x);
				detail->QueryFloatAttribute("pos_y", &pos_y);
				detail->QueryFloatAttribute("left", &left);
				detail->QueryFloatAttribute("top", &top);
				detail->QueryFloatAttribute("right", &right);
				detail->QueryFloatAttribute("bottom", &bottom);
				Camera* camera = new Camera();
				camera->setCam(pos_x, pos_y);
				camera->setBoundBox(left, top, right, bottom);
				camera->setCamdefault(pos_x, pos_y);

				cameras.insert(make_pair(id, camera));

				//CGame::GetInstance()->SetCam(cameras[start]);
				DebugOut(L"cameras size = %d\n", cameras.size());
			}
			CGame::GetInstance()->SetCam(cameras[start]);
		}
		node = info->FirstChildElement("LoadMAP");
		file = node->Attribute("file");
		filepath = node->Attribute("filepath");
		gamemap = new CGameMap();
		gamemap->FromTMX(filepath, file);
		gamemap->MapOBJECTS(filepath, file);
		DebugOut(L"[INFO]Staet load : %d \n", id);

		node = info->FirstChildElement("LoadLayer");
		float x, y;
		node->QueryFloatAttribute("x", &x);
		node->QueryFloatAttribute("y", &y);
		player = CPlayer::GetInstance();
		player->SetPosition(x, y);
		player->SetAnimationSet(CAnimations::GetInstance());
		//objects.push_back(player);
		DebugOut(L"[INFO] GameMap:   \n");
	}
	hud = new HUD();


	CGame::GetInstance()->GetInstance()->getCamera()->setCamdefault(0, 750);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void MapScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	player->Update(dt, &coObjects);
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float px, py;
	player->GetPosition(px, py);
	CGame::GetInstance()->GetInstance()->getCamera()->update(px, py);

	hud->Update(dt);
	if (canvas != NULL) canvas->Update(dt);
}

void MapScene::Render()
{
	gamemap->Render(CGame::GetInstance());
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Pre_Render();
	player->Pre_Render();
	gamemap->ReRender(CGame::GetInstance());
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	player->Render();


	if (canvas != NULL) canvas->Render();
	hud->Render();
}


void MapScene::Unload()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}
