#pragma once

#include "Scence.h"
#include "PlayScence.h"

class MapScene :
    public CScene
{
    CPlayer* player = NULL;					
    vector<LPGAMEOBJECT> objects;
    vector<LPGAMEOBJECT> earseobjects;
    vector<LPGAMEOBJECT> addobjects;
    CGameMap* gamemap;
    HUD* hud;
    Canvas* canvas;
    unordered_map<int, LPCamera> cameras;

    void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);
public:
    MapScene(int id, string filePath);
    virtual void Load();
    virtual void Update(DWORD dt);
    virtual void Render();
    virtual void Unload();
    void LoadSource();
    virtual CPlayer* GetPlayer() { return player; }
    virtual void addCanvas(Canvas* canvas) { this->canvas = canvas; }
    virtual void addobject(LPGAMEOBJECT object) { addobjects.push_back(object); }
    virtual void delobject(LPGAMEOBJECT object) { earseobjects.push_back(object); }
    virtual LPCamera getCamera(int id_camera) { return cameras[id_camera]; }
    virtual void newObject(LPGAMEOBJECT object, string stringGrid = "") { addobjects.push_back(object); }
};

class CMapScenceKeyHandler : public CScenceKeyHandler
{
public:
    virtual void KeyState(BYTE* states);
    virtual void OnKeyDown(int KeyCode);
    virtual void OnKeyUp(int KeyCode);
    CMapScenceKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};
