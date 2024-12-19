#pragma once
#include "GameObject.h"


#define POWER_BBOX_WIDTH 12
#define POWER_BBOX_HEIGHT 24

#define POWER_DIE_TIMEOUT 500

#define POWER_STATE_IDLE 100

#define ID_ANI_POWER_IDLE 7000

class CPower : public CGameObject
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
	CPower(float x, float y);
	virtual void SetState(int state);
};