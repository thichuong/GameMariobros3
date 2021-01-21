#pragma once
#include "GameObject.h"
#include "Sprites.h"

#define NODE_BBOX_WIDTH		48
#define NODE_BBOX_HEIGHT	48

#define NODE_ANI "node_ani"
#define NODE_ANI_numM "node_ani_M"
#define NODE_ANI_START "node_ani_start"
#define NODE_ANI_NUM1 "node_ani_num1"
#define NODE_ANI_NUM2 "node_ani_num2"
#define NODE_ANI_NUM3 "node_ani_num3"
#define NODE_ANI_NUM4 "node_ani_num4"
#define NODE_ANI_NUM5 "node_ani_num5"
#define NODE_ANI_NUM6 "node_ani_num6"

enum class TypeNode
{
    
    start,
    num1,
    num2,
    num3,
    num4,
    num5,
    num6,
    numM, 
    bonus,
    Nodenone
    
};

class CNode :
    public CGameObject
{
    int nodeID;
    TypeNode typenode;
    int IDscene;
   
    CSprite* spritesNode[9];
public:

    bool up, down, left, right;
    
    CNode();
    virtual void Render();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual void SetAnimationSet(CAnimations* ani_set);
    virtual void CollisionObject(LPGAMEOBJECT obj, float nx, float ny);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
    void SetTypeNode(string type);
   
};

