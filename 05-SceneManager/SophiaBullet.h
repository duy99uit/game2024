#pragma once
#include "GameObject.h"
#define BULLET_BBOX_WIDTH	9
#define BULLET_BBOX_HEIGHT	9

#define BULLET_EXTRA_RANGE  5

#define BULLET_SPEED_X	0.2f
#define BULLET_SPEED_Y	0.2f
#define BULLET_DIE_TIMEOUT 160

	

#define BULLET_MOVING_ANI		6000
#define BULLET_COLLISION_BRICK		6001
#define BULLET_EXPLODE		6002
class SophiaBullet :
    public CGameObject
{
    virtual void Render();
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void OnCollisionWithBlackWalker(LPCOLLISIONEVENT e);
    void OnCollisionWithBeetleHead(LPCOLLISIONEVENT e);
    ULONGLONG die_start;
public:
    SophiaBullet();
    SophiaBullet(float x, float y, float vx, float vy); 
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    void SetState(int state);

 /*   void OnNoCollision(DWORD dt);*/
    void OnCollisionWith(LPCOLLISIONEVENT e);
};