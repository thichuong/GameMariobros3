#include <iostream>
#include <fstream>

#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	key_handler = new CPlayScenceKeyHandler(this);
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
	CTextures* textures = CTextures::GetInstance();

	textures->Add("tex-mario", L"Textures\\Mario\\mario_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-enemy", L"Textures\\Enemy\\enemy_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-intro", L"Textures\\Misc\\intro_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-misc", L"Textures\\Misc\\misc_x3.png", D3DCOLOR_XRGB(255, 255, 255));
	//textures->Add("tex-ui", L"Textures\\Misc\\UI_x3.png", D3DCOLOR_XRGB(255, 255, 255));

	PlaySprites = CSprites::GetInstance();
	
	//_ParseSection_SPRITES("Textures/Sprites/IntroDB.xml");
	//_ParseSection_SPRITES("Textures/Sprites/MiscDB.xml");
	_ParseSection_SPRITES("Textures/Sprites/MarioDB.xml");
	//_ParseSection_SPRITES("Textures/Sprites/EnemyDB.xml");
	
	//_ParseSection_SPRITES("Textures/Sprites/UiDB.xml");

	PlayAni = CAnimations::GetInstance();
	//_ParseSection_ANIMATIONS("Textures/Animations/IntroAnim.xml");
	//_ParseSection_ANIMATIONS("Textures/Animations/MiscAnim.xml");
	_ParseSection_ANIMATIONS("Textures/Animations/MarioAnim.xml");
	//_ParseSection_ANIMATIONS("Textures/Animations/EnemyAnim.xml");
	
	//_ParseSection_ANIMATIONS("Textures/Animations/UiAnim.xml");
}
void CPlayScene::_ParseSection_SPRITES(string line)
{
	TiXmlDocument doc(line.c_str());
	
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* texture = root->FirstChildElement();

		string textureID = texture->Attribute("textureId");
		LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(textureID);

		for (TiXmlElement* node = texture->FirstChildElement(); node != nullptr; node = node->NextSiblingElement())
		{
			string spriteID = node->Attribute("id");
			int left, top, width, height;
			node->QueryIntAttribute("left", &left);
			node->QueryIntAttribute("top", &top);
			node->QueryIntAttribute("width", &width);
			node->QueryIntAttribute("height", &height);
			
			left = left * 3 ;
			top = top * 3 ;
			width = width * 3;
			height = height * 3;

			PlaySprites->Add(spriteID, left, top, left + width, top + height, tex);
		}
	}
}
void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	TiXmlDocument doc(line.c_str());
	
	if (doc.LoadFile())
	{
		TiXmlElement* root = doc.RootElement();
		TiXmlElement* info = root->FirstChildElement();

		string gameObjectID = info->Attribute("gameObjectId");
		string textureID = info->Attribute("textureId");
		
		

		for (TiXmlElement* node = info->FirstChildElement(); node != nullptr; node = node->NextSiblingElement())
		{
			string aniId = node->Attribute("aniId");
			float frameTime;
			node->QueryFloatAttribute("frameTime", &frameTime);
			//string name = node->Attribute("id");
			
			LPANIMATION ani = new CAnimation();
			DebugOut(L"[INFO] Loading aniId = : %s \n", ToLPCWSTR(aniId));
			for (TiXmlElement* sprNode = node->FirstChildElement(); sprNode != nullptr; sprNode = sprNode->NextSiblingElement())
			{
				string id = sprNode->Attribute("id");
				LPSPRITE sprite = PlaySprites->Get(id);
				ani->Add(sprite);
				DebugOut(L"					 Loading Id = : %s \n", ToLPCWSTR(id));
			}
			
			PlayAni->Add(aniId, ani);
			
			
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

	for (int i = 1; i < tokens.size(); i++)
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
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());

	 
	x = x * 3;
	y = y * 3;
	string ani_set_id = tokens[3].c_str();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(100,290); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(); break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(); break;
	case OBJECT_TYPE_PORTAL:
		{	
			float r = atof(tokens[4].c_str());
			float b = atof(tokens[5].c_str());
			int scene_id = atoi(tokens[6].c_str());
			obj = new CPortal(x, y, r, b, scene_id);
		}
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);
	//CAnimations ani_set = CAnimationSets::GetInstance()->Get(ani_set_id);

	obj->SetAnimationSet(PlayAni);
	objects.push_back(obj);
}

void CPlayScene::Load()
{
	LoadSource();
	gamemap = new CGameMap();
	gamemap->FromTMX("Textures/Maps", "world-1-1-map.tmx");
	objects = gamemap->MapOBJECTS(PlayAni);
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);
	
	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	
	player = new CMario();
	player->SetPosition(100,900);
	//CAnimations ani_set = CAnimationSets::GetInstance()->Get(ani_set_id);
	
	player->SetAnimationSet(PlayAni);
	objects.push_back(player);
	
	f.close();

	//CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	CGame *game = CGame::GetInstance();
	cx -= game->GetScreenWidth() / 2;
	cy -= (game->GetScreenHeight() / 2) *1.5;
	if (cx < 0)
		cx = 0;
	if (cy < 0)
		cy = 0;
	CGame::GetInstance()->SetCamPos(cx, cy);
	
}

void CPlayScene::Render()
{
	gamemap->Render(CGame::GetInstance());
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	mario->OnKeyDown(KeyCode)
	
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	mario->KeyState(states);
	// disable control key when Mario die 
	
}