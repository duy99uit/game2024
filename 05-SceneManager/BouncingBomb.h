#pragma once
#include "GameObject.h"


#define BOUNCING_BOMB_BBOX_WIDTH 8
#define BOUNCING_BOMB_BBOX_HEIGHT 8

#define BOUNCING_BOMB_DIE_TIMEOUT 500
#define BOUNCING_BOMB_PREPARE_TIME 1000

#define BOUNCING_BOMB_STATE_FALLING 100
#define BOUNCING_BOMB_STATE_PREPARE_EXPLOXE 101
#define BOUNCING_BOMB_STATE_EXPLODE 102

#define ID_ANI_BOUNCING_BOMB_FALLING 7001
#define ID_ANI_BOUNCING_BOMB_PREPARE_EXPLODE 7002

class CBouncingBomb : public CGameObject
{
protected:
	float ax;
	float ay;
	BOOLEAN isOnPlatform;

	ULONGLONG die_start;
	ULONGLONG prepareExploxe_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBouncingBomb(float x, float y);
	virtual void SetState(int state);
};