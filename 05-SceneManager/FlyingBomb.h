#pragma once
#include "GameObject.h"

#define FLYINGBOMB_GRAVITY 0.002f
#define FLYINGBOMB_FLYING_SPEED 0.1f
#define FLYINGBOMB_ESCAPING_SPEED 0.1f
#define FLYINGBOMB_WALKING_ACCELERATION 0.05f


#define FLYINGBOMB_BBOX_WIDTH 16
#define FLYINGBOMB_BBOX_HEIGHT 16
#define FLYINGBOMB_BBOX_WIDTH_IDLE 150
#define FLYINGBOMB_BBOX_HEIGHT_IDLE 400
#define FLYINGBOMB_BBOX_HEIGHT_DIE 7

#define FLYINGBOMB_DIE_TIMEOUT 500

#define FLYINGBOMB_STATE_FLYING_LEFT 102
#define FLYINGBOMB_STATE_FLYING_RIGHT 103
#define FLYINGBOMB_STATE_ESCAPING_LEFT 104
#define FLYINGBOMB_STATE_ESCAPING_RIGHT 105
#define FLYINGBOMB_STATE_THROWING_LEFT 106
#define FLYINGBOMB_STATE_THROWING_RIGHT 17
#define FLYINGBOMB_STATE_DIE 200

#define ID_ANI_FLYINGBOMB_DIE 5101
#define ID_ANI_FLYINGBOMB_FLYING_LEFT 5102
#define ID_ANI_FLYINGBOMB_ESCAPING_LEFT 5103
#define ID_ANI_FLYINGBOMB_FLYING_RIGHT 5104
#define ID_ANI_FLYINGBOMB_ESCAPING_RIGHT 5105
#define ID_ANI_FLYINGBOMB_THROWING_RIGHT 5106
#define ID_ANI_FLYINGBOMB_THROWING_LEFT 5107

class CFlyingBomb : public CGameObject
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
	void OnCollisionWithSophia(LPCOLLISIONEVENT e);

public:
	CFlyingBomb(float x, float y);
	virtual void SetState(int state);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void ThrowBomb();
};