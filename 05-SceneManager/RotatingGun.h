#pragma once
#include "GameObject.h"


#define ROTATINGGUN_BBOX_WIDTH 16
#define ROTATINGGUN_BBOX_HEIGHT 16
#define ROTATINGGUN_BBOX_WIDTH_IDLE 110
#define ROTATINGGUN_BBOX_HEIGHT_IDLE 100
#define ROTATINGGUN_BBOX_HEIGHT_DIE 7

#define ROTATINGGUN_DIE_TIMEOUT 500

#define ROTATINGGUN_STATE_SHOOT 101
#define ROTATINGGUN_STATE_IDLE 100
#define ROTATINGGUN_STATE_DIE 102

#define ID_ANI_ROTATINGGUN_SHOOT 7012
#define ID_ANI_ROTATINGGUN_IDLE 7011



class CRotatingGun : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithSophia(LPCOLLISIONEVENT e);


public:
	CRotatingGun(float x, float y);
	virtual void SetState(int state);
};