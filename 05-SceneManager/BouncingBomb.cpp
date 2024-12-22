
#include "BouncingBomb.h"
#include "Game.h"
#include "debug.h"
CBouncingBomb::CBouncingBomb(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(BOUNCING_BOMB_STATE_FALLING);
	aniId = ID_ANI_BOUNCING_BOMB_FALLING;
	vy = -0.07f;
	vx = -0.02f;
	isOnPlatform = false;
}

void CBouncingBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BOUNCING_BOMB_BBOX_WIDTH / 2;
	top = y - BOUNCING_BOMB_BBOX_HEIGHT / 2;
	right = left + BOUNCING_BOMB_BBOX_WIDTH;
	bottom = top + BOUNCING_BOMB_BBOX_HEIGHT;
}

void CBouncingBomb::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	/*isOnPlatform = false;*/
	DebugOut(L"CBouncingBomb::OnNoCollision >>>>> %d\n", x, vx);
};
void CBouncingBomb::OnCollisionWith(LPCOLLISIONEVENT e)
{
	DebugOut(L"CSophia::OnCollisionWith 11111");


	if (e->ny != 0 && e->obj->IsBlocking())
	{
		DebugOut(L"CSophia::OnCollisionWith 1111");
		vy = 0;
		vx = 0;
		isOnPlatform = true;
		SetState(BOUNCING_BOMB_STATE_PREPARE_EXPLOXE);
	}

}


void CBouncingBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if ((state == BOUNCING_BOMB_STATE_PREPARE_EXPLOXE) && (GetTickCount64() - prepareExploxe_start > BOUNCING_BOMB_PREPARE_TIME))
	{
		isDeleted = true;
		

	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBouncingBomb::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBouncingBomb::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case  BOUNCING_BOMB_STATE_PREPARE_EXPLOXE:
		aniId = ID_ANI_BOUNCING_BOMB_PREPARE_EXPLODE;
		prepareExploxe_start = GetTickCount64();
		break;
	}
}