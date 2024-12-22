#include "SophiaBullet.h"
#include "Sophia.h"
#include "PlayScene.h"


SophiaBullet::SophiaBullet(float x, float y, float vx, float vy) :CGameObject(x, y, vx, vy)
{
	/*SetState(BLACKWALKER_STATE_WALKING_LEFT);*/
	aniId = BULLET_MOVING_ANI;
	/*vx = BULLET_SPEED_X;*/
	/*vy = 0.09f;*/
	vx = vx;
	vy = vy;
}

void SophiaBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBlackWalker*>(e->obj)) {
		OnCollisionWithBlackWalker(e);
	}
	if (dynamic_cast<CBeetleHead*>(e->obj)) {
		OnCollisionWithBeetleHead(e);
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
			SetState(BULLET_EXPLODE);

		}
	}
	
}
void SophiaBullet::OnCollisionWithBeetleHead(LPCOLLISIONEVENT e)
{
	CBeetleHead* beettleHead = dynamic_cast<CBeetleHead*>(e->obj);
	if (e->nx != 0 || e->ny != 0)
	{
		if (beettleHead->GetState() != BEETLEHEAD_STATE_DIE)
		{
			beettleHead->SetState(BEETLEHEAD_STATE_DIE);
			SetState(BULLET_EXPLODE);

		}
	}

}

void SophiaBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	x += vx * dt;
	y += vy * dt;

	if ((state == BULLET_EXPLODE) && (GetTickCount64() - die_start > BULLET_DIE_TIMEOUT / 3))
	{
		isDeleted = true;
		return;
	}

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
void SophiaBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_EXPLODE:
		vx = 0;
		vy = 0;
		break;
	}
}
