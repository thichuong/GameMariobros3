#pragma once
#include "GameObject.h"
#include "Resource.h"
class CPlayer;

#define MARIO_WALKING_SPEED  0.2f
#define MARIO_WALKING_SPEED_UP  0.0003f
#define MARIO_WALKING_SPEED_DOWN  0.0015f
#define MARIO_RUNING_SPEED  0.6f
#define MARIO_MIN_SPEED  0.1f
//0.1f
#define MARIO_JUMP_SPEED_Y  0.02f
#define MARIO_JUMP_SPEED_Y_UP  0.004f
#define MARIO_JUMP_SPEED_Y_HIGH  0.65f
#define MARIO_JUMP_SPEED_Y_SUPER  0.75f
#define MARIO_FLY_SPEED_Y  1.25f
#define MARIO_JUMP_DEFLECT_SPEED  0.4f
#define MARIO_GRAVITY  0.003f
#define MARIO_DIE_DEFLECT_SPEED  0.5f
#define WARP_SPEED 0.2f

#define MARIO_TIME_ATTACK 200
#define MARIO_TIME_COOLDOWN 400

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
#define FLOAT "float"
#define ATTACK "attack"
#define HOLD "hold"
#define HOLD_IDLE "hold_idle"
#define HOLD_FALL "hold_fall"
#define WARP_HOR_IDLE "Warp-hor"


#define MARIO_ANI_SMALL "-small-mario"
#define MARIO_ANI_BIG "-big-mario"
#define MARIO_ANI_FIRE "-fire-mario"
#define MARIO_ANI_RACCOON "-raccoon-mario"

#define Mario_small "small"
#define big "big"
#define fire "fire"
#define raccoon "raccoon"
#define none "none"

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE	3
#define MARIO_LEVEL_RACCOON	4



#define MARIO_BIG_BBOX_WIDTH  42.0f
#define MARIO_BIG_BBOX_HEIGHT 80.0f
#define MARIO_BIG_BBOX_HEIGHT_CROUCHING 54
#define MARIO_BIG_BBOX_CROUCHING 26
#define MARIO_HOLD 15


#define MARIO_SMALL_BBOX_WIDTH  39
#define MARIO_SMALL_BBOX_HEIGHT 45

#define TIME_WARP 700
#define MARIO_UNTOUCHABLE_TIME 5000
#define MAX_METTER 7
#define MIN_METTER 0.004f

enum class MoveStates
{
	Idle,
	Walk,
	Run,
	Crouch,
	Attack
};

enum class JumpStates
{
	Stand,
	Jump,
	Super,
	Fall,
	
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
	ULONGLONG untouchable_start;
	ULONGLONG timeattack;
	ULONGLONG  timecooldown;
	ULONGLONG  ani_timeattack;
	ULONGLONG time_wrap;
	bool walking;
	bool onGround; 
	bool canHighjump;
	MarioStateSet Mariostate, preMariostate;
	TypeWarp marioWarp;
	bool slowFall;
	float start_x;			// initial position of Mario at scene
	float start_y; 
	
	float attack;
	
	CPlayer* player;

	float metter;
	DWORD time_metter;

public: 
	CMario(float x = 0, float y = 0);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void Pre_Render();
	void UpdateVx(DWORD dt);
	void UpdateCollisions(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	void UpdateReward(DWORD dt);

	virtual void OnKeyUp(int keyCode);
	virtual void OnKeyDown(int keyCode);
	virtual void KeyState(BYTE* state);
	
	void SetState(int state);
	void SetLevel(string l);
	string GetLevel();
	virtual void DownLevel() ;
	virtual void SetLevel(int lv);
	CPlayer* getPlayer() { return player; }
	void setPlayer(CPlayer* player) { this->player = player;}
	void holdObj(LPGAMEOBJECT obj); 
	void kickObj();

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void ChangeState();

	virtual void SetMoveState(MoveStates e) ;
	virtual void SetJumpState(JumpStates e) ;

	JumpStates GetJumpState() { return Mariostate.jump; }
	void Reset();
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) =0;

	float getMetter() { return metter; }

	void Warp(TypeWarp warp);
	
};