#pragma once
#include "GameObject.h"

#define GUNWALKER_GRAVITY 0.002f
#define GUNWALKER_WALKING_SPEED 0.05f
#define GUNWALKER_WALKING_ACCELERATION 0.05f


#define GUNWALKER_BBOX_WIDTH 16
#define GUNWALKER_BBOX_HEIGHT 24

#define GUNWALKER_DIE_TIMEOUT 500

#define GUNWALKER_STATE_WALKING_RIGHT 102
#define GUNWALKER_STATE_WALKING_LEFT 104


#define GUNWALKER_STATE_DIE 200


#define ID_ANI_GUNWALKER_STATE_WALKING_RIGHT 7050
#define ID_ANI_GUNWALKER_STATE_WALKING_LEFT 7051



class CGunWalker : public CGameObject
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


public:
	CGunWalker(float x, float y);
	virtual void SetState(int state);
};