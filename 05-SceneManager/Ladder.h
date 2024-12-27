#pragma once
#pragma once
#include "GameObject.h"

#define LADDER_BBOX_WIDTH 6
#define LADDER_BBOX_HEIGHT 250

#define ID_ANI_LADDER 8001




class CLadder : public CGameObject
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
	CLadder(float x, float y);
	virtual void SetState(int state);
	int GetNewX() { return newX; }
	int GetNewY() { return newY; }
};