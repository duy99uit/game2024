#pragma once
#include "GameObject.h"

#define CHECKPOINT_BBOX_WIDTH 32
#define CHECKPOINT_BBOX_HEIGHT 32

#define ID_ANI_CHECKPOINT 8000




class CCheckPoint : public CGameObject
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
	CCheckPoint(float x, float y);
	CCheckPoint(float x, float y, float newX, float newY);
	virtual void SetState(int state);
	int GetNewX()  { return newX; }
	int GetNewY()  { return newY; }
};