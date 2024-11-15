#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

// big
#define BIG_JASON_WALKING_SPEED		0.1f
#define BIG_JASON_STATE_DIE				-10
#define BIG_JASON_STATE_IDLE			0
#define BIG_JASON_STATE_IDLE_LEFT			1
#define BIG_JASON_STATE_IDLE_RIGHT			2
#define BIG_JASON_STATE_IDLE_UP			3
#define BIG_JASON_STATE_IDLE_DOWN			4
#define BIG_JASON_STATE_WALKING_RIGHT	100
#define BIG_JASON_STATE_WALKING_LEFT	200
#define BIG_JASON_STATE_WALKING_UP	201
#define BIG_JASON_STATE_WALKING_DOWN	202
// small
#define SMALL_JASON_STATE_IDLE			1000
#define SMALL_JASON_STATE_IDLE_LEFT			1001
#define SMALL_JASON_STATE_IDLE_RIGHT			1002
#define SMALL_JASON_STATE_IDLE_UP			1003
#define SMALL_JASON_STATE_IDLE_DOWN			1004
#define SMALL_JASON_STATE_WALKING_RIGHT	1100
#define SMALL_JASON_STATE_WALKING_LEFT	1200
#define SMALL_JASON_STATE_WALKING_UP	1201
#define SMALL_JASON_STATE_WALKING_DOWN	1202



#pragma region ANIMATION_ID

// jason big
#define ID_ANI_BIG_JASON_IDLE_RIGHT 400
#define ID_ANI_BIG_JASON_IDLE_LEFT 401
#define ID_ANI_BIG_JASON_IDLE_UP 402
#define ID_ANI_BIG_JASON_IDLE_DOWN 403
#define ID_ANI_BIG_JASON_WALKING_RIGHT 500
#define ID_ANI_BIG_JASON_WALKING_LEFT 501
#define ID_ANI_BIG_JASON_WALKING_UP 502
#define ID_ANI_BIG_JASON_WALKING_DOWN 503

// jason small
#define ID_ANI_SMALL_JASON_IDLE_RIGHT 700
#define ID_ANI_SMALL_JASON_IDLE_LEFT 701
#define ID_ANI_SMALL_JASON_IDLE_UP 702
#define ID_ANI_SMALL_JASON_IDLE_DOWN 703
#define ID_ANI_SMALL_JASON_WALKING_RIGHT 800
#define ID_ANI_SMALL_JASON_WALKING_LEFT 801
#define ID_ANI_SMALL_JASON_WALKING_UP 802
#define ID_ANI_SMALL_JASON_WALKING_DOWN 803




#define ID_ANI_JASON_DIE 999


#pragma endregion




#define	JASON_LEVEL_SMALL	1
#define	JASON_LEVEL_BIG		2

#define JASON_BIG_BBOX_WIDTH  14
#define JASON_BIG_BBOX_HEIGHT 24

#define JASON_SMALL_BBOX_WIDTH  13
#define JASON_SMALL_BBOX_HEIGHT 12


#define JASON_UNTOUCHABLE_TIME 2500

class CJason : public CGameObject
{
	float maxVx;
	float maxVy;
	float ax;				// acceleration on x 
	float ay;
	BOOLEAN isMovingX;

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	int GetAniIdBig();
	int GetAniIdSmall();
public:
	CJason(float x, float y) : CGameObject(x, y)
	{
		maxVx = 0.0f;
		maxVy = 0.0f;
		ax = 0.0f;
		ay = 0.0f; 
		vy = 0.00f;
		vx = 0.00f;
		isMovingX = true;
		level = JASON_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		// init state is idle right
		state = SMALL_JASON_STATE_IDLE_RIGHT;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	int getState() { return state; };
	void HandleKeyState();
	void HandleKeyUp(int KeyCode);
	void HandleKeyDown(int KeyCode);

	int IsCollidable()
	{ 
		return (state != BIG_JASON_STATE_DIE); 
	}

	int IsBlocking() { return (state != BIG_JASON_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};