#include "Bullet.h"
#include "Sophia.h"
#include "PlayScene.h"


Bullet::Bullet(float x, float y, float vx, float vy) :CGameObject(x, y, vx, vy)
{
	/*SetState(BLACKWALKER_STATE_WALKING_LEFT);*/
	aniId = JASON_S_BULLET_MOVING_ANI;
	/*vx = BULLET_SPEED_X;*/
	/*vy = 0.09f;*/
	vx = vx;
	vy = vy;
}

void Bullet::OnCollisionWith(LPCOLLISIONEVENT e)

{
	if (e->obj->IsBlocking())
	{
		DebugOut(L"CSophia::OnCollisionWith 1111");
		vx = 0;
		vy = 0;
		SetState(BULLET_EXPLODE);
	}
	if (dynamic_cast<CBlackWalker*>(e->obj)) {
		OnCollisionWithBlackWalker(e);
	}
	if (dynamic_cast<CBeetleHead*>(e->obj)) {
		OnCollisionWithBeetleHead(e);
	}
	if (dynamic_cast<CFlyingBomb*>(e->obj)) {
		OnCollisionWithFlyingBomb(e);
	}
	if (dynamic_cast<CRotatingGun*>(e->obj)) {
		OnCollisionWithRotatingGun(e);
	}
	if (dynamic_cast<CPlatformWalker*>(e->obj)) {
		OnCollisionWithPlatformWalker(e);
	}

}
void Bullet::OnCollisionWithBlackWalker(LPCOLLISIONEVENT e)
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
void Bullet::OnCollisionWithBeetleHead(LPCOLLISIONEVENT e)
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
void Bullet::OnCollisionWithFlyingBomb(LPCOLLISIONEVENT e)
{
	CFlyingBomb* flyingBomb = dynamic_cast<CFlyingBomb*>(e->obj);
	if (e->nx != 0 || e->ny != 0)
	{
		if (flyingBomb->GetState() != FLYINGBOMB_STATE_DIE)
		{
			flyingBomb->SetState(FLYINGBOMB_STATE_DIE);
			SetState(BULLET_EXPLODE);

		}
	}

}
void Bullet::OnCollisionWithWall(LPCOLLISIONEVENT e)
{

	if (e->nx != 0 || e->ny != 0)
	{
		SetState(BULLET_EXPLODE);
	}

}

void Bullet::OnCollisionWithRotatingGun(LPCOLLISIONEVENT e)
{
	CRotatingGun* rotatingGun = dynamic_cast<CRotatingGun*>(e->obj);

	if (rotatingGun->GetState() != ROTATINGGUN_STATE_DIE)
	{
		rotatingGun->SetState(ROTATINGGUN_STATE_DIE);
		SetState(BULLET_EXPLODE);

	}
}

void Bullet::OnCollisionWithPlatformWalker(LPCOLLISIONEVENT e)
{
	CPlatformWalker* platformWalker = dynamic_cast<CPlatformWalker*>(e->obj);

	if (platformWalker->GetState() != PLATFORMWALKER_STATE_DIE)
	{
		platformWalker->SetState(PLATFORMWALKER_STATE_DIE);
		SetState(BULLET_EXPLODE);

	}
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

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

void Bullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void Bullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}
void Bullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BULLET_EXPLODE:
		aniId = BULLET_EXPLODE;
		vx = 0;
		vy = 0;
		break;
	}
}
