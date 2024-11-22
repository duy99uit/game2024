#include "BeetleHead.h"
#include "Game.h"

CBeetleHead::CBeetleHead(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(BEETLEHEAD_STATE_WALKING_RIGHT);
	aniId = ID_ANI_BEETLEHEAD_WALKING_RIGHT;
}

void CBeetleHead::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BEETLEHEAD_BBOX_WIDTH / 2;
	top = y - BEETLEHEAD_BBOX_HEIGHT / 2;
	right = left + BEETLEHEAD_BBOX_WIDTH;
	bottom = top + BEETLEHEAD_BBOX_HEIGHT;
}

void CBeetleHead::OnNoCollision(DWORD dt)
{
};

void CBeetleHead::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();
	x += vx * dt;
	if (x >= vW) {
		SetState(BEETLEHEAD_STATE_WALKING_LEFT);
	}
	else if (x <= 0) {
		SetState(BEETLEHEAD_STATE_WALKING_RIGHT);
	}

	CGameObject::Update(dt, coObjects);
}


void CBeetleHead::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	/*RenderBoundingBox();*/
}

void CBeetleHead::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BEETLEHEAD_STATE_DIE:
		die_start = GetTickCount64();
		aniId = ID_ANI_BEETLEHEAD_DIE;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case BEETLEHEAD_STATE_WALKING_LEFT:
		aniId = ID_ANI_BEETLEHEAD_WALKING_LEFT;
		vx = -BEETLEHEAD_WALKING_SPEED;
		nx = -1;
		ax = -BEETLEHEAD_WALKING_ACCELERATION;
		break;
	case BEETLEHEAD_STATE_WALKING_RIGHT:
		aniId = ID_ANI_BEETLEHEAD_WALKING_RIGHT;
		vx = BEETLEHEAD_WALKING_SPEED;
		nx = 1;
		ax = BEETLEHEAD_WALKING_ACCELERATION;
		break;
	}
}