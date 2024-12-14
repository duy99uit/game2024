#include "SophiaBullet.h"
#include "Sophia.h"
#include "PlayScene.h"

SophiaBullet::SophiaBullet(float bx, float by, bool up, bool right) {

}
SophiaBullet::SophiaBullet(float x, float y) :CGameObject(x, y)
{
	/*SetState(BLACKWALKER_STATE_WALKING_LEFT);*/
	aniId = BULLET_ANI_SET_ID;
	vx = 0.05f;
	/*vy = 0.09f;*/
}

void SophiaBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBlackWalker*>(e->obj)) {
		OnCollisionWithBlackWalker(e);
	}

}
void SophiaBullet::OnCollisionWithBlackWalker(LPCOLLISIONEVENT e)
{
	CBlackWalker* blackWalker = dynamic_cast<CBlackWalker*>(e->obj);
	if (e->nx != 0 || e->ny != 0)
	{
		if (blackWalker->GetState() != BLACKWALKER_STATE_DIE)
		{
			blackWalker->SetState(BLACKWALKER_STATE_DIE);

		}
	}
	
}


void SophiaBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	x += vx * dt;
	y += vy * dt;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void SophiaBullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void SophiaBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}