#include "Game.h"
#include "JellyFish.h"

CJellyFish::CJellyFish(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(JELLYFISH_STATE_WALKING_RIGHT);
	aniId = ID_ANI_JELLYFISH_STATE_WALKING_RIGHT;
}

void CJellyFish::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - JELLYFISH_BBOX_WIDTH / 2;
	top = y - JELLYFISH_BBOX_HEIGHT / 2;
	right = left + JELLYFISH_BBOX_WIDTH;
	bottom = top + JELLYFISH_BBOX_HEIGHT;
}

void CJellyFish::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CJellyFish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();


	if ((state == JELLYFISH_STATE_DIE) && (GetTickCount64() - die_start > JELLYFISH_DIE_TIMEOUT / 3))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CJellyFish::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/*if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlatformWalker*>(e->obj)) return;*/
}


void CJellyFish::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CJellyFish::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case JELLYFISH_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}
