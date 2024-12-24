#pragma once
#include "GameObject.h"

#define JELLYFISH_GRAVITY 0.002f
#define JELLYFISH_WALKING_SPEED 0.05f
#define JELLYFISH_WALKING_ACCELERATION 0.05f


#define JELLYFISH_BBOX_WIDTH 16
#define JELLYFISH_BBOX_HEIGHT 16

#define JELLYFISH_DIE_TIMEOUT 500

#define JELLYFISH_STATE_WALKING_RIGHT 102
#define JELLYFISH_STATE_WALKING_LEFT 104


#define JELLYFISH_STATE_DIE 200


#define ID_ANI_JELLYFISH_STATE_WALKING_RIGHT 7070
#define ID_ANI_JELLYFISH_STATE_WALKING_LEFT 7071



class CJellyFish : public CGameObject
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
	CJellyFish(float x, float y);
	virtual void SetState(int state);
};