#include "GunWalker.h"
#include "Game.h"

CGunWalker::CGunWalker(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(GUNWALKER_STATE_WALKING_RIGHT);
	aniId = ID_ANI_GUNWALKER_STATE_WALKING_RIGHT;
}

void CGunWalker::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - GUNWALKER_BBOX_WIDTH / 2;
	top = y - GUNWALKER_BBOX_HEIGHT / 2;
	right = left + GUNWALKER_BBOX_WIDTH;
	bottom = top + GUNWALKER_BBOX_HEIGHT;
}

void CGunWalker::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGunWalker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();


	if ((state == GUNWALKER_STATE_DIE) && (GetTickCount64() - die_start > GUNWALKER_DIE_TIMEOUT / 3))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGunWalker::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/*if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlatformWalker*>(e->obj)) return;*/
}


void CGunWalker::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGunWalker::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GUNWALKER_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}
