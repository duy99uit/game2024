#pragma once
#include "GameObject.h"

#define BEETLEHEAD_GRAVITY 0.002f
#define BEETLEHEAD_WALKING_SPEED 0.08f
#define BEETLEHEAD_WALKING_ACCELERATION 0.05f


#define BEETLEHEAD_BBOX_WIDTH 12
#define BEETLEHEAD_BBOX_HEIGHT 24
#define BEETLEHEAD_BBOX_HEIGHT_DIE 7

#define BEETLEHEAD_DIE_TIMEOUT 500

#define BEETLEHEAD_STATE_WALKING 100
#define BEETLEHEAD_STATE_WALKING_LEFT 102
#define BEETLEHEAD_STATE_WALKING_RIGHT 103
#define BEETLEHEAD_STATE_DIE 200

#define ID_ANI_BEETLEHEAD_WALKING 5000
#define ID_ANI_BEETLEHEAD_DIE 5001
#define ID_ANI_BEETLEHEAD_WALKING_LEFT 5002
#define ID_ANI_BEETLEHEAD_WALKING_RIGHT 5003

class CBeetleHead : public CGameObject
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
	CBeetleHead(float x, float y);
	virtual void SetState(int state);
};