#pragma once

#include "Scence.h"
#include "PlayScence.h"

class MapScene :
    public CScene
{
    CPlayer* player = NULL;					
    vector<LPGAMEOBJECT> objects;
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
};

