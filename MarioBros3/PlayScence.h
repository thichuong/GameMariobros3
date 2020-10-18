#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "GameMap.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"

using namespace std;

//string MARIO_DB = "Textures/Sprites/MarioDB.xml";
//string ENEMY_DB = "Textures/Sprites/EnemyDB.xml";
//string INTRO_DB = "Textures/Sprites/IntroDB.xml";
//string MISC_DB = "Textures/Sprites/MiscDB.xml";
//string UI_DB = "Textures/Sprites/UiDB.xml";
//
//string MARIO_ANIM = "Textures/Animations/MarioAnim.xml";
//string ENEMY_ANIM = "Textures/Animations/EnemyAnim.xml";
//string INTRO_ANIM = "Textures/Animations/IntroAnim.xml";
//string MISC_ANIM = "Textures/Animations/MiscAnim.xml";
//string UI_ANIM = "Textures/Animations/UiAnim.xml";

class CPlayScene: public CScene
{
protected: 
	CMario *player;					// A play scene has to have player, right? 
	CAnimations* PlayAni;
	CSprites* PlaySprites;
	vector<LPGAMEOBJECT> objects;
	CGameMap* gamemap;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);

public: 
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void LoadSource();
	CMario * GetPlayer() { return player; } 

	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

