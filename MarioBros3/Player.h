#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "SmallMario.h"
#include "BigMario.h"
#include "FireMario.h"
#include "RaccoonMario.h"
#include "MapMario.h"
#include <unordered_map>
#include "WarpPipe.h"
#include "ItemCard.h"

#define DOWN_LEVEL_TIME 1000



using namespace std;
class CPlayer : public CGameObject
{
    static  CPlayer* __instance;
    unordered_map<string, CMario*> ListMario;
    CMario* playMario;
    
    MapMario* mapmario;
    string levelMario;
    DWORD downleveltime;
public: 
    long score;

    int life, coin;
    
    Card cards[3];
    LPGAMEOBJECT holdobject;
    vector<CFireBullet*> bullets;


    string GetScore();
    string Getcoin();
    string GetLife();
    
    void AddScore(long x);
    void AddCoin(int x);
    void AddLife(int x);

    CPlayer();
    void SwitchToMario(string state);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
    virtual void Render();
    virtual void Pre_Render() ;
   
    void OnKeyUp(int keyCode) { playMario->OnKeyUp(keyCode); }
    void OnKeyDown(int keyCode) { playMario->OnKeyDown(keyCode); }
    void KeyState(BYTE* state) { playMario->KeyState(state); }
    
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void SetAnimationSet(CAnimations* ani_set);
    void SetPosition(float x, float y);
    void Downlevel();
    void SetLevel(int lv);
    int getMetter();
    CMario* getMario() { return playMario; }
    MapMario* getMapMario() { return mapmario; }

    void Warp(TypeWarp warp);
    static  CPlayer* GetInstance();
    string GetlevelMario() { return levelMario; }
};

