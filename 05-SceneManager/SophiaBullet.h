#pragma once
#include "GameObject.h"
#define BULLET_BBOX_WIDTH	9
#define BULLET_BBOX_HEIGHT	9

#define BULLET_EXTRA_RANGE  5

#define BULLET_SPEED_X	0.1f
#define BULLET_SPEED_Y	0.1f

#define BULLET_ANI_RIGHT		0
#define BULLET_ANI_LEFT			1	

#define BULLET_MOVING_ANI		6000
class SophiaBullet :
    public CGameObject
{
    virtual void Render();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void OnCollisionWithBlackWalker(LPCOLLISIONEVENT e);
public:
    SophiaBullet();
    SophiaBullet(float x, float y, float vx, float vy); 
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }

 /*   void OnNoCollision(DWORD dt);*/
    void OnCollisionWith(LPCOLLISIONEVENT e);
};