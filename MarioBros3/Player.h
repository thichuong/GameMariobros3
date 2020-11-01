#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "SmallMario.h"
#include "BigMario.h"
#include "FireMario.h"
#include "RaccoonMario.h"
#include <unordered_map>

#define small "small"
#define big "big"
#define fire "fire"
#define raccoon "raccoon"
#define DOWN_LEVEL_TIME 1000
using namespace std;
class CPlayer : public CGameObject
{
    static  CPlayer* __instance;
    unordered_map<string, CMario*> ListMario;
    CMario* playMario;
    string levelMario;
    DWORD downleveltime;
public:
    CPlayer();
    void SwitchToMario(string state);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
    virtual void Render();
    void OnKeyUp(int keyCode) { playMario->OnKeyUp(keyCode); }
    void OnKeyDown(int keyCode) { playMario->OnKeyDown(keyCode); }
    void KeyState(BYTE* state) { playMario->KeyState(state); }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void SetAnimationSet(CAnimations* ani_set);
    void SetPosition(float x, float y);
    void Downlevel();

    static  CPlayer* GetInstance();
};

