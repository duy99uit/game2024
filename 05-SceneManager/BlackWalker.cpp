#include "BlackWalker.h"
#include "Game.h"

CBlackWalker::CBlackWalker(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(BLACKWALKER_STATE_WALKING_LEFT);
	aniId = ID_ANI_BLACKWALKER_WALKING_LEFT;
}

void CBlackWalker::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BLACKWALKER_BBOX_WIDTH / 2;
	top = y - BLACKWALKER_BBOX_HEIGHT / 2;
	right = left + BLACKWALKER_BBOX_WIDTH;
	bottom = top + BLACKWALKER_BBOX_HEIGHT;
}

void CBlackWalker::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBlackWalker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();
	/*x += vx * dt;
	if (x >= vW) {
		SetState(BLACKWALKER_STATE_WALKING_LEFT);
	}
	else if (x <= 0) {
		SetState(BLACKWALKER_STATE_WALKING_RIGHT);
	}*/

	if ((state == BLACKWALKER_STATE_DIE) && (GetTickCount64() - die_start > BLACKWALKER_DIE_TIMEOUT/3))
	{
		isDeleted = true;
		return;
	}

	/*CGameObject::Update(dt, coObjects);*/
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBlackWalker::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBlackWalker*>(e->obj)) return;
}


void CBlackWalker::Render()
{
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBlackWalker::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BLACKWALKER_STATE_DIE:
		die_start = GetTickCount64();
	/*	aniId = ID_ANI_BLACKWALKER_WALKING_LEFT;*/
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BLACKWALKER_STATE_WALKING_LEFT:
		aniId = ID_ANI_BLACKWALKER_WALKING_LEFT;
		vx = -BLACKWALKER_WALKING_SPEED;
		nx = -1;
		ax = -0.05f;
		break;
	case BLACKWALKER_STATE_WALKING_RIGHT:
		aniId = ID_ANI_BLACKWALKER_WALKING_RIGHT;
		vx = BLACKWALKER_WALKING_SPEED/10;
		nx = 1;
		ax = BLACKWALKER_WALKING_ACCELERATION;
		break;
	}
}
