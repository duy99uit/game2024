#include "BeeHead.h"
#include "Game.h"

CBeeHead::CBeeHead(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(BEEHEAD_STATE_WALKING_RIGHT);
	aniId = ID_ANI_BEEHEAD_STATE_WALKING_RIGHT;
}

void CBeeHead::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BEEHEAD_BBOX_WIDTH / 2;
	top = y - BEEHEAD_BBOX_HEIGHT / 2;
	right = left + BEEHEAD_BBOX_WIDTH;
	bottom = top + BEEHEAD_BBOX_HEIGHT;
}

void CBeeHead::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBeeHead::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();


	if ((state == BEEHEAD_STATE_DIE) && (GetTickCount64() - die_start > BEEHEAD_DIE_TIMEOUT / 3))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBeeHead::OnCollisionWith(LPCOLLISIONEVENT e)
{
	/*if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlatformWalker*>(e->obj)) return;*/
}


void CBeeHead::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CBeeHead::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BEEHEAD_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}
