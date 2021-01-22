#pragma once

#include <d3dx9.h>
#include <string>
#include "GameObject.h"
#include "KeyEventHandler.h"
#include "Player.h"
#include "Camera.h"
#include "Canvas.h"

using namespace std;

class CScene
{
protected:
	CKeyEventHandler * key_handler;
	int id;
	string sceneFilePath;
	int switchID;
public: 
	CScene(int id, string filePath);
	CKeyEventHandler * GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
	virtual void addobject(LPGAMEOBJECT object) {};
	virtual void delobject(LPGAMEOBJECT object) {};
	virtual void newObject(LPGAMEOBJECT object , string stringGrid = "") {};
	virtual CPlayer* GetPlayer() { return NULL; }
	virtual LPCamera getCamera(int id_camera) { return NULL; }
	virtual void addCanvas(Canvas* canvas) {};
	void setSwitchID(int idScence) { switchID = idScence; }
};
typedef CScene * LPSCENE;


class CScenceKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CScenceKeyHandler(CScene *s) :CKeyEventHandler() { scence = s; }
};