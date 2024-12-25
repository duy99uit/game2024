#include "CheckPoint.h"
#include "Game.h"
#include "debug.h"

CCheckPoint::CCheckPoint(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	aniId = ID_ANI_CHECKPOINT;
}
CCheckPoint::CCheckPoint(float x, float y, float newX, float newY)
{
	die_start = -1;
	this->newX = newX;
	this->newY = newY;
	DebugOut(L"CCheckPoint >>>>> %d\n", newX);
	aniId = ID_ANI_CHECKPOINT;
}

void CCheckPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CHECKPOINT_BBOX_WIDTH / 2;
	top = y - CHECKPOINT_BBOX_HEIGHT / 2;
	right = left + CHECKPOINT_BBOX_WIDTH;
	bottom = top + CHECKPOINT_BBOX_HEIGHT;
}

void CCheckPoint::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CCheckPoint::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCheckPoint::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}


void CCheckPoint::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CCheckPoint::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	
	}
}
