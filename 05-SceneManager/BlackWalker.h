#pragma once
#include "GameObject.h"

#define BLACKWALKER_GRAVITY 0.002f
#define BLACKWALKER_WALKING_SPEED 0.01f
#define BLACKWALKER_WALKING_ACCELERATION 0.05f


#define BLACKWALKER_BBOX_WIDTH 12
#define BLACKWALKER_BBOX_HEIGHT 24
#define BLACKWALKER_BBOX_HEIGHT_DIE 7

#define BLACKWALKER_DIE_TIMEOUT 500

#define BLACKWALKER_STATE_WALKING 100
#define BLACKWALKER_STATE_WALKING_LEFT 102
#define BLACKWALKER_STATE_WALKING_RIGHT 103
#define BLACKWALKER_STATE_DIE 200

#define ID_ANI_BLACKWALKER_WALKING 5000
#define ID_ANI_BLACKWARKER_DIE 5001
#define ID_ANI_BLACKWALKER_WALKING_LEFT 5002
#define ID_ANI_BLACKWALKER_WALKING_RIGHT 5003

// tag detect should create power or not
#define BLACKWALKER_TYPE_POWER 1
#define BLACKWALKER_JUMPING_STACKS	2
#define BLACKWALKER_TIME_WALKING			500

class CBlackWalker : public CGameObject
{
protected:
	float ax;
	float ay;
	int jumpingStacks = 0;

	ULONGLONG die_start;
	ULONGLONG walkingTimer = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	

public:
	CBlackWalker(float x, float y, int tag);
	virtual void SetState(int state);
};