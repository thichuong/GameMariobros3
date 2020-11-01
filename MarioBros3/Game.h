#pragma once

#include <unordered_map>

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>


#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Textures.h"
#include "Scence.h"
#include "tinyXML.h"
using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024
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

class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	LPKEYEVENTHANDLER keyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;

	int screen_width;
	int screen_height; 

	unordered_map<int, LPSCENE> scenes;
	int current_scene; 

	void _ParseSection_SETTINGS(string line);
	void _ParseSection_SCENES(string line);

	
public:
	void InitKeyboard();
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { keyHandler = handler; }
	void Init(HWND hWnd);
	void Draw(int x, int y, int xPivot, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void Draw(int x, int y, int xPivot, D3DXVECTOR2 vectorflip, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void DrawFlipX(int x, int y, int xPivot, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	
	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	void Load(string gameFile);
	
	LPSCENE GetCurrentScene() { return scenes[current_scene]; }
	void SwitchScene(int scene_id);

	int GetScreenWidth() { return screen_width; }
	int GetScreenHeight() { return screen_height; }
	int GetScamX() { return cam_x; }
	int GetScamY() { return cam_y; }

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }

	static CGame * GetInstance();

	~CGame();
};


