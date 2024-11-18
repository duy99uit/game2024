#pragma once
#include "GameObject.h"

#define SOPHIA_GRAVITY 0.002f
#define SOPHIA_WALKING_SPEED 0.08f
#define SOPHIA_WALKING_ACCELERATION 0.05f


#define SOPHIA_BBOX_WIDTH 12
#define SOPHIA_BBOX_HEIGHT 24
#define SOPHIA_BBOX_HEIGHT_DIE 7

#define SOPHIA_DIE_TIMEOUT 500

#define SOPHIA_STATE_WALKING_LEFT 102
#define SOPHIA_STATE_WALKING_RIGHT 103
#define SOPHIA_STATE_DIE 200

#define ID_ANI_SOPHIA_DIE 2001
#define ID_ANI_SOPHIA_WALKING_LEFT 2002
#define ID_ANI_SOPHIA_WALKING_RIGHT 2003

class CSophia : public CGameObject
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

public:
	CSophia(float x, float y);
	virtual void SetState(int state);
};