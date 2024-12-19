#pragma once
#include "GameObject.h"


#define BOUNCING_BOMB_BBOX_WIDTH 12
#define BOUNCING_BOMB_BBOX_HEIGHT 24

#define BOUNCING_BOMB_DIE_TIMEOUT 500

#define BOUNCING_BOMB_STATE_FALLING 100
#define BOUNCING_BOMB_STATE_EXPLODE 100

#define ID_ANI_BOUNCING_BOMB_FALLING 7001

class CBouncingBomb : public CGameObject
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
	CBouncingBomb(float x, float y);
	virtual void SetState(int state);
};