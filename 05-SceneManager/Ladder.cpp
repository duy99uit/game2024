#include "Ladder.h"
#include "Game.h"
#include "debug.h"

CLadder::CLadder(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	aniId = ID_ANI_LADDER;
}

void CLadder::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LADDER_BBOX_WIDTH / 2;
	top = y - LADDER_BBOX_HEIGHT / 2;
	right = left + LADDER_BBOX_WIDTH;
	bottom = top + LADDER_BBOX_HEIGHT;
}

void CLadder::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLadder::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLadder::OnCollisionWith(LPCOLLISIONEVENT e)
{

}


void CLadder::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CLadder::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	}
}
