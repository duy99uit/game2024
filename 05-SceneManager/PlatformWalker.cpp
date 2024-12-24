#include "PlatformWalker.h"
#include "Game.h"

CPlatformWalker::CPlatformWalker(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(R_PLATFORMWALKER_STATE_WALKING_UP);
	aniId = ID_ANI_L_PLATFORMWALKER_STATE_WALKING_RIGHT;
}

void CPlatformWalker::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLATFORMWALKER_BBOX_WIDTH / 2;
	top = y - PLATFORMWALKER_BBOX_HEIGHT / 2;
	right = left + PLATFORMWALKER_BBOX_WIDTH;
	bottom = top + PLATFORMWALKER_BBOX_HEIGHT;
}

void CPlatformWalker::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPlatformWalker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();
	

	if ((state == PLATFORMWALKER_STATE_DIE) && (GetTickCount64() - die_start > PLATFORMWALKER_DIE_TIMEOUT / 3))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlatformWalker::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/*if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlatformWalker*>(e->obj)) return;*/
}


void CPlatformWalker::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPlatformWalker::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLATFORMWALKER_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}
