#pragma once
#include "GameObject.h"

#define BEEHEAD_GRAVITY 0.002f
#define BEEHEAD_WALKING_SPEED 0.05f
#define BEEHEAD_WALKING_ACCELERATION 0.05f


#define BEEHEAD_BBOX_WIDTH 16
#define BEEHEAD_BBOX_HEIGHT 16

#define BEEHEAD_DIE_TIMEOUT 500

#define BEEHEAD_STATE_WALKING_RIGHT 102
#define BEEHEAD_STATE_WALKING_LEFT 104


#define BEEHEAD_STATE_DIE 200


#define ID_ANI_BEEHEAD_STATE_WALKING_RIGHT 7060
#define ID_ANI_BEEHEAD_STATE_WALKING_LEFT 7061



class CBeeHead : public CGameObject
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
	CBeeHead(float x, float y);
	virtual void SetState(int state);
};