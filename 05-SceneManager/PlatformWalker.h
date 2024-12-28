#pragma once
#include "GameObject.h"
#include "PlayScene.h"

#define PLATFORMWALKER_GRAVITY 0.002f
#define PLATFORMWALKER_WALKING_SPEED 0.01f
#define PLATFORMWALKER_WALKING_ACCELERATION 0.05f


#define PLATFORMWALKER_BBOX_WIDTH 16
#define PLATFORMWALKER_BBOX_HEIGHT 16
#define PLATFORMWALKER_BBOX_HEIGHT_DIE 7

#define PLATFORMWALKER_DIE_TIMEOUT 500

#define R_PLATFORMWALKER_STATE_WALKING_UP 101
#define R_PLATFORMWALKER_STATE_WALKING_RIGHT 102
#define R_PLATFORMWALKER_STATE_WALKING_DOWN 103
#define R_PLATFORMWALKER_STATE_WALKING_LEFT 104

#define L_PLATFORMWALKER_STATE_WALKING_UP 111
#define L_PLATFORMWALKER_STATE_WALKING_RIGHT 112
#define L_PLATFORMWALKER_STATE_WALKING_DOWN 113
#define L_PLATFORMWALKER_STATE_WALKING_LEFT 114

#define PLATFORMWALKER_STATE_DIE 200

#define ID_ANI_R_PLATFORMWALKER_STATE_WALKING_UP 7034
#define ID_ANI_R_PLATFORMWALKER_STATE_WALKING_RIGHT 7031
#define ID_ANI_R_PLATFORMWALKER_STATE_WALKING_DOWN 7032
#define ID_ANI_R_PLATFORMWALKER_STATE_WALKING_LEFT 7033

#define ID_ANI_L_PLATFORMWALKER_STATE_WALKING_UP 7042
#define ID_ANI_L_PLATFORMWALKER_STATE_WALKING_RIGHT 7043
#define ID_ANI_L_PLATFORMWALKER_STATE_WALKING_DOWN 7044
#define ID_ANI_L_PLATFORMWALKER_STATE_WALKING_LEFT 7041



class CPlatformWalker : public CGameObject
{
protected:
	float ax;
	float ay;
	boolean onplatform = true;
	LPGAMEOBJECT current_platform;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	virtual void OnCollisionWithPlatform(LPCOLLISIONEVENT e);


public:
	CPlatformWalker(float x, float y, int init_state, float px, float py, float cell_width, float cell_height, int length, int sprite_begin, int sprite_middle, int sprite_end);
	virtual void SetState(int state);
};