#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED  0.2f
#define MARIO_WALKING_SPEED_UP  0.002f
#define MARIO_WALKING_SPEED_DOWN  0.005f
#define MARIO_RUNING_SPEED  0.5f
#define MARIO_MIN_SPEED  0.1f
//0.1f
#define MARIO_JUMP_SPEED_Y  0.3f
#define MARIO_JUMP_SPEED_Y_SPEED  0.004f
#define MARIO_JUMP_SPEED_Y_HIGH  0.6f
#define MARIO_JUMP_SPEED_Y_SUPER  0.9f
#define MARIO_FLY_SPEED_Y  1.3f
#define MARIO_JUMP_DEFLECT_SPEED  0.2f
#define MARIO_GRAVITY  0.003f
#define MARIO_DIE_DEFLECT_SPEED  0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_DIE				100

#define MARIO_ANI_DIE				"ani-small-mario-idle"

#define IDLE			"idle"
#define WALK		"walk"
#define SKID	"skid"
#define RUN	"run"
#define CROUCH "crouch"
#define JUMP		"jump"
#define FLY	"fly"
#define FALL "fall"

#define MARIO_ANI_SMALL "-small-mario"
#define MARIO_ANI_BIG "-big-mario"
#define MARIO_ANI_FIRE "-fire-mario"
#define MARIO_ANI_RACCOON "-raccoon-mario"

#define small "small"
#define big "big"
#define fire "fire"
#define raccoon "raccoon"
#define none "none"

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE	3
#define MARIO_LEVEL_RACCOON	4



#define MARIO_BIG_BBOX_WIDTH  42
#define MARIO_BIG_BBOX_HEIGHT 80
#define MARIO_BIG_BBOX_HEIGHT_CROUCHING 54

#define MARIO_SMALL_BBOX_WIDTH  39
#define MARIO_SMALL_BBOX_HEIGHT 45

#define MARIO_UNTOUCHABLE_TIME 5000

enum class MoveStates
{
	Idle,
	Walk,
	Run,
	Crouch
};

enum class JumpStates
{
	Stand,
	Jump,
	Super,
	Fall,
	Attack
};

struct MarioStateSet
{
	MoveStates movement;
	JumpStates jump;
};
class CMario : public CGameObject
{
protected:
	string changeMario;
	int untouchable;
	DWORD untouchable_start;
	bool walking;
	bool onGround; 
	bool canHighjump;
	MarioStateSet Mariostate, preMariostate;

	float start_x;			// initial position of Mario at scene
	float start_y; 
	float ax;
public: 
	CMario(float x = 0, float y = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render() = 0;
	void UpdateVx();
	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);
	virtual void KeyState(BYTE* state);
	void SetState(int state);
	void SetLevel(int l);
	string GetLevel();
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void ChangeState();
	virtual void SetMoveState(MoveStates e) ;
	virtual void SetJumpState(JumpStates e) ;
	void Reset();
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) {};
};