#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameMap.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "HUD.h"

#include "Resource.h"


#define BREAK_UPDATE 1000

using namespace std;





class CPlayScene: public CScene
{
protected: 
	CPlayer *player = NULL;					// A play scene has to have player, right? 
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> earseobjects;
	vector<LPGAMEOBJECT> addobjects;
	unordered_map<int, LPCamera> cameras;
	CGameMap* gamemap ;
	HUD* hud ;
	Canvas* canvas ;
	ULONGLONG break_Update;
	int start_x, start_y;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

public: 
	CPlayScene(int id, string filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	virtual void addobject(LPGAMEOBJECT object) { addobjects.push_back(object); }
	virtual void delobject(LPGAMEOBJECT object) { earseobjects.push_back(object); }
	void LoadSource();
	virtual CPlayer* GetPlayer() { return player; }
	virtual LPCamera getCamera(int id_camera) { return cameras[id_camera]; }
	virtual void addCanvas(Canvas* canvas) { this->canvas = canvas; }
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) ;
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

