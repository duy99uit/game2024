#pragma once
#include "GameObject.h"

#define SOPHIA_GRAVITY 0.002f
#define SOPHIA_WALKING_SPEED 0.08f
#define SOPHIA_WALKING_ACCELERATION 0.05f
#define SOPHIA_JUMP_SPEED_Y		0.5f


#define SOPHIA_BBOX_WIDTH 12
#define SOPHIA_BBOX_HEIGHT 24
#define SOPHIA_BBOX_HEIGHT_DIE 7

#define SOPHIA_DIE_TIMEOUT 500

#define SOPHIA_STATE_WALKING_LEFT 102
#define SOPHIA_STATE_WALKING_RIGHT 103
#define SOPHIA_STATE_IDLE_LEFT 104
#define SOPHIA_STATE_IDLE_RIGHT 105
#define SOPHIA_STATE_JUMP 106
#define SOPHIA_STATE_DIE 200

#define ID_ANI_SOPHIA_DIE 2001
#define ID_ANI_SOPHIA_WALKING_LEFT 1502
#define ID_ANI_SOPHIA_WALKING_RIGHT 1503

#define SOPHIA_UNTOUCHABLE_TIME 2500
#define SOPHIA_GRAVITY			0.002f

class CSophia : public CGameObject
{
	float maxVx;
	float maxVy;
	float ax;				// acceleration on x 
	float ay;

	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;

public:
	CSophia(float x, float y) : CGameObject(x, y)
	{
		maxVx = 0.0f;
		ax = 0.0f;
	/*	ay = -SOPHIA_GRAVITY;*/
		ay = -SOPHIA_GRAVITY;

	/*	maxVx = 0.0f;*/
		maxVy = 0.0f;
	/*	ax = 0.0f;
		ay = 0.0f;*/
		vy = 0.00f;
		vx = 0.00f;
		level = 1;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		// init state is idle right
		state = SOPHIA_STATE_IDLE_RIGHT;
		aniId = ID_ANI_SOPHIA_WALKING_RIGHT;
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
		return (state != SOPHIA_STATE_DIE);
	}

	int IsBlocking() { return (state != SOPHIA_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};