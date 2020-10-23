#pragma once
#include "GameObject.h"

const float MARIO_WALKING_SPEED = 0.5f;
const float MARIO_WALKING_SPEED_UP = 0.01f;
const float MARIO_WALKING_SPEED_DOWN = 0.002f;
//0.1f
#define MARIO_JUMP_SPEED_Y		0.3f
#define MARIO_JUMP_SPEED_Y_HIGH	0.004f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.003f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400

#define MARIO_ANI_BIG_IDLE		"ani-big-mario-idle"
#define MARIO_ANI_SMALL_IDLE		"ani-small-mario-idle"

#define MARIO_ANI_BIG_WALKING		"ani-big-mario-walk"
#define MARIO_ANI_SMALL_WALKING		"ani-small-mario-walk"

#define MARIO_ANI_LEFT
#define MARIO_ANI_DIE				"ani-small-mario-idle"

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  42
#define MARIO_BIG_BBOX_HEIGHT 80

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
	High,
	Fall
};

struct MarioStateSet
{
	MoveStates movement;
	JumpStates jump;
};
class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	bool walking;
	bool onGround; 
	bool canHighjump;
	MarioStateSet Mariostate;

	float start_x;			// initial position of Mario at scene
	float start_y; 
	float ax;
public: 
	CMario(float x = 10.0f, float y = 1290.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void OnKeyUp(int keyCode);
	void OnKeyDown(int keyCode);
	void KeyState(BYTE* state);
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void SetVectorMario();

	void Reset();
	virtual void SetAnimationSet(CAnimations* ani_set);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};