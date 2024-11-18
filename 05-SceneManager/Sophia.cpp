#include "Sophia.h"
#include "Game.h"

CSophia::CSophia(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	aniId = ID_ANI_SOPHIA_WALKING_RIGHT;
	SetState(SOPHIA_STATE_WALKING_RIGHT);
}

void CSophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SOPHIA_BBOX_WIDTH / 2;
	top = y - SOPHIA_BBOX_HEIGHT / 2;
	right = left + SOPHIA_BBOX_WIDTH;
	bottom = top + SOPHIA_BBOX_HEIGHT;
}

void CSophia::OnNoCollision(DWORD dt)
{
};

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();
	x += vx * dt;
	if (x >= vW) {
		SetState(SOPHIA_STATE_WALKING_LEFT);
	}
	else if (x <= 0) {
		SetState(SOPHIA_STATE_WALKING_RIGHT);
	}

	CGameObject::Update(dt, coObjects);
}


void CSophia::Render()
{
	int aniId = ID_ANI_SOPHIA_WALKING_RIGHT;
	if (state == SOPHIA_STATE_DIE)
	{
		aniId = ID_ANI_SOPHIA_DIE;
	}
	if (vx < 0)
	{
		aniId = ID_ANI_SOPHIA_WALKING_LEFT;
	}
	if (vx >= 0)
	{
		aniId = ID_ANI_SOPHIA_WALKING_RIGHT;
	}



	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	/*RenderBoundingBox();*/
}

void CSophia::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOPHIA_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		vx = -SOPHIA_WALKING_SPEED;
		nx = -1;
		ax = -SOPHIA_WALKING_ACCELERATION;
		break;
	case SOPHIA_STATE_WALKING_RIGHT:
		vx = SOPHIA_WALKING_SPEED;
		nx = 1;
		ax = SOPHIA_WALKING_ACCELERATION;
		break;
	}
}