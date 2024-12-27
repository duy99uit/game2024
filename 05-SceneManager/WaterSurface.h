#pragma once
#pragma once
#include "GameObject.h"

#define WATERSURFACE_BBOX_WIDTH 3500
#define WATERSURFACE_BBOX_HEIGHT 300

#define ID_ANI_WATERSURFACE 8001




class CWaterSurface : public CGameObject
{
	int newX;
	int newY;
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


public:
	CWaterSurface(float x, float y);
	virtual void SetState(int state);
	int GetNewX() { return newX; }
	int GetNewY() { return newY; }
};