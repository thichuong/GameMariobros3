#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"


using namespace std;

CPlayScene::CPlayScene(int id, string filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
	
	gamemap = NULL;
	canvas = NULL;
	hud = new HUD();
	start_x = 0;
	start_y = 0;
	break_Update = 0;

	grid = NULL;
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3

#define OBJECT_TYPE_PORTAL	50

#define MAX_SCENE_LINE 1024


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	string texID = tokens[0].c_str();
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::LoadSource()
{
	//CTextures* textures = CTextures::GetInstance();

	//textures->Add("tex-mario", L"Textures\\Mario\\mario_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-enemy", L"Textures\\Enemy\\enemy_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-intro", L"Textures\\Misc\\intro_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-misc", L"Textures\\Misc\\misc_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-ui", L"Textures\\Misc\\UI_x3.png", D3DCOLOR_XRGB(255, 255, 255));

	//PlaySprites = CSprites::GetInstance();
	
	//_ParseSection_SPRITES("Textures/Sprites/IntroDB.xml");
	//_ParseSection_SPRITES("Textures/Sprites/MiscDB.xml");
	//_ParseSection_SPRITES("Textures/Sprites/MarioDB.xml");
	//_ParseSection_SPRITES("Textures/Sprites/EnemyDB.xml");
	
	//_ParseSection_SPRITES("Textures/Sprites/UiDB.xml");

	//PlayAni = CAnimations::GetInstance();
	//_ParseSection_ANIMATIONS("Textures/Animations/IntroAnim.xml");
	//_ParseSection_ANIMATIONS("Textures/Animations/MiscAnim.xml");
	//_ParseSection_ANIMATIONS("Textures/Animations/MarioAnim.xml");
	//_ParseSection_ANIMATIONS("Textures/Animations/EnemyAnim.xml");
	
	//_ParseSection_ANIMATIONS("Textures/Animations/UiAnim.xml");
}
void CPlayScene::_ParseSection_SPRITES(string line)
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
void CPlayScene::_ParseSection_ANIMATIONS(string line)
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

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	string ani_set_id = tokens[0].c_str();

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (unsigned int i = 1; i < tokens.size(); i++)
	{
		string ani_id = tokens[i].c_str();
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	

}

void CPlayScene::Load()
{
	//LoadSource();
	/*playsprites = csprites::getinstance();
	playani = canimations::getinstance();*/
	float x, y;
	int start;
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
				if (detail->Attribute("auto"))
				{
					camera->BlockCam();
					TiXmlElement* path = detail->FirstChildElement("Path");
					float cam_vx;
					path->QueryFloatAttribute("speed", &cam_vx);
					camera->setSpeed(cam_vx);
					DebugOut(L"[cameras VX] = %f \n", cam_vx);
				}


				cameras.insert(make_pair(id, camera));
				
				//CGame::GetInstance()->SetCam(cameras[start]);
				
			}
			CGame::GetInstance()->SetCam(cameras[start]);
		}
		node = info->FirstChildElement("LoadMAP");
		file = node->Attribute("file");
		filepath = node->Attribute("filepath");

		CreatGrid(filepath, file);

		gamemap = new CGameMap();
		gamemap->FromTMX(filepath, file);
		gamemap->MapOBJECTS(filepath, file);
		DebugOut(L"[INFO]Staet load : %d \n", id);
		
		node = info->FirstChildElement("LoadLayer");
		
		node->QueryFloatAttribute("x", &x);
		node->QueryFloatAttribute("y", &y);
		player = CPlayer::GetInstance();
		player->SetPosition(x, y);
		player->SetAnimationSet(CAnimations::GetInstance());
		player->time_game = 300;
		player->tick_time_game = 0;
		start_x = x;
		start_y = y ;
		DebugOut(L"[INFO MARIO] Position : %f , %f \n", x, y);
		//objects.push_back(player);
		DebugOut(L"[INFO] GameMap:   \n");
		
		
	}
	hud = new HUD();
	
	canvas = NULL;
	gridObject = new vector<LPGAMEOBJECT>();
	//break_Update = GetTickCount64();

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	if (GetTickCount64() -   break_Update < BREAK_UPDATE)
	{
		dt = 0;
		
	}
	else
	{
		vector<LPGAMEOBJECT> coObjects;

		float l, t, r, b;
		CGame::GetInstance()->getCamera()->getBoundBox(l, t, r, b);
		grid->Update(l, t, r, b);
		gridObject = grid->getActiveGameObject();
		for (size_t i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);
		}
		for (size_t i = 0; i < gridObject->size(); i++)
		{
			coObjects.push_back(gridObject->at(i));
		}

		player->Update(dt, &coObjects);

		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);
		}
		for (size_t i = 0; i < gridObject->size(); i++)
		{
			gridObject->at(i)->Update(dt, &coObjects);
		}


		if (earseobjects.size() > 0)
		{
			for (auto e : earseobjects)
			{
				for (size_t i = 0; i < objects.size(); i++)
				{
					if (objects[i] == e) objects.erase(objects.begin() + i);
				}
			}
			for (auto e : earseobjects) delete e;
			earseobjects.clear();
		}
		if (addobjects.size() > 0)
		{
			for (auto e : addobjects)
			{
				objects.push_back(e);
			}

			addobjects.clear();
		}
		// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
		if (player == NULL) return;

		// Update camera to follow mario
		float px, py;
		player->GetPosition(px, py);
		CGame::GetInstance()->GetInstance()->getCamera()->update(px, py, dt);

		hud->Update(dt);
		if (canvas != NULL) canvas->Update(dt);
		if (start_x != 0 && start_y != 0)
		{
			player->SetPosition(start_x, start_y);
			start_x = 0;
			start_y = 0;
		}
	}

	if (switchID != 0)
		CGame::GetInstance()->SwitchScene(switchID);
}

void CPlayScene::Render()
{
	gamemap->Render(CGame::GetInstance());

	//GRID RENDER
	for (unsigned int i = 0; i < gridObject->size(); i++)
		gridObject->at(i)->Pre_Render();

	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Pre_Render();

	player->Pre_Render();

	for (unsigned int i = 0; i < gridObject->size(); i++)
		gridObject->at(i)->Render();

	gamemap->ReRender(CGame::GetInstance());
	for (unsigned int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	
	player->Render();

	
	if (canvas != NULL) canvas->Render();
	hud->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (unsigned int i = 0; i < objects.size(); i++)
		delete objects[i];
	switchID = 0;
	objects.clear();
	cameras.clear();

	//player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CPlayer*mario = ((CPlayScene*)scence)->GetPlayer();
	mario->OnKeyDown(KeyCode);
	if (KeyCode == DIK_0)
	{
		float camw, camh;
		camw = CGame::GetInstance()->GetScreenWidth();
		camh = CGame::GetInstance()->GetScreenHeight();
		float x, y;
		mario->GetPosition(x, y);
		LPGAMEOBJECT object = new CGoomba();
		object->SetAnimationSet(CAnimations::GetInstance());
		object->SetPosition(x + camw/2, y - camh/2);
		((CPlayScene*)scence)->addobject(object);
	}
	if (KeyCode == DIK_9)
	{

		float camw, camh;
		camw = CGame::GetInstance()->GetScreenWidth();
		camh = CGame::GetInstance()->GetScreenHeight();
		float x, y;
		mario->GetPosition(x, y);
		LPGAMEOBJECT object = new CKoopas();
		object->SetAnimationSet(CAnimations::GetInstance());
		object->SetPosition(x + camw / 2, y - camh / 2);
		((CPlayScene*)scence)->addobject(object);
	}
	if (KeyCode == DIK_R)
	{
		mario->SetPosition(6903, 500);
		CGame::GetInstance()->SetCam(((CPlayScene*)scence)->getCamera(0));
	}
	if (KeyCode == DIK_E)
	{
		CGame::GetInstance()->SwitchScene(1);
	}
	if (KeyCode == DIK_T)
	{
		mario->SetPosition(5842, 350);
		CGame::GetInstance()->SetCam(((CPlayScene*)scence)->getCamera(0));
		CGame::GetInstance()->getCamera()->setCam(5842, 224);
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CPlayer *mario = ((CPlayScene*)scence)->GetPlayer();
	mario->KeyState(states);
	// disable control key when Mario die 
	
}
void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CPlayer* mario = ((CPlayScene*)scence)->GetPlayer();
	mario->OnKeyUp(KeyCode);
}