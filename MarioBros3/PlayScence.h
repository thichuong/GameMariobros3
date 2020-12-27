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

#define camY 750
#define YHUD 200


using namespace std;





class CPlayScene: public CScene
{
protected: 
	CPlayer *player;					// A play scene has to have player, right? 
	//CAnimations* PlayAni;
	//CSprites* PlaySprites;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> earseobjects;
	CGameMap* gamemap;
	int camYdefault;
	HUD* hud;

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
	virtual void addobject(LPGAMEOBJECT object) { objects.push_back(object); }
	virtual void delobject(LPGAMEOBJECT object) { earseobjects.push_back(object); }
	void LoadSource();
	virtual CPlayer* GetPlayer() { return player; }

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

