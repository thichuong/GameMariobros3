#pragma once

#include "Scence.h"
#include "PlayScence.h"
#include "TitteIntro.h"

class IntroScene :
    public CScene
{
    vector<LPGAMEOBJECT> objects;
    CGameMap* gamemap;
    TitteIntro* titte;
    unordered_map<int, LPCamera> cameras;

    void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);
public:
    IntroScene(int id, string filePath);
    virtual void Load();
    virtual void Update(DWORD dt);
    virtual void Render();
    virtual void Unload();
    void LoadSource();
    virtual CPlayer* GetPlayer() { return NULL; }
    virtual LPCamera getCamera(int id_camera) { return cameras[id_camera]; }
};

class CIntroSceneKeyHandler : public CScenceKeyHandler
{
public:
    virtual void KeyState(BYTE* states);
    virtual void OnKeyDown(int KeyCode);
    virtual void OnKeyUp(int KeyCode);
    CIntroSceneKeyHandler(CScene* s) :CScenceKeyHandler(s) {};
};

