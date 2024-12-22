
#include "FlyingBomb.h"
#include "Game.h"
#include "PlayScene.h"
CFlyingBomb::CFlyingBomb(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(FLYINGBOMB_STATE_FLYING_LEFT);
	aniId = ID_ANI_FLYINGBOMB_FLYING_LEFT;
}

void CFlyingBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == FLYINGBOMB_STATE_FLYING_LEFT) {
		left = x - FLYINGBOMB_BBOX_WIDTH_IDLE / 2;
		top = y - FLYINGBOMB_BBOX_HEIGHT_IDLE / 2;
		right = left + FLYINGBOMB_BBOX_WIDTH_IDLE;
		bottom = top + FLYINGBOMB_BBOX_HEIGHT_IDLE;
	}
	else {
		left = x - FLYINGBOMB_BBOX_WIDTH / 2;
		top = y - FLYINGBOMB_BBOX_HEIGHT / 2;
		right = left + FLYINGBOMB_BBOX_WIDTH;
		bottom = top + FLYINGBOMB_BBOX_HEIGHT;
	}
	
	
}

void CFlyingBomb::OnNoCollision(DWORD dt)
{
};

void CFlyingBomb::OnCollisionWith(LPCOLLISIONEVENT e)

{
	DebugOut(L"CFlyingBomb::OnCollisionWith 22222");
	if (dynamic_cast<CSophia*>(e->obj)) {
		OnCollisionWithSophia(e);
	}


}

void CFlyingBomb::OnCollisionWithSophia(LPCOLLISIONEVENT e)
{
	CSophia* sophia = dynamic_cast<CSophia*>(e->obj);
	if (e->nx != 0 || e->ny != 0)
	{
		if (sophia->GetState() != SOPHIA_STATE_DIE && state != FLYINGBOMB_STATE_THROWING_LEFT)
		{
			/*sophia->SetState(SOPHIA_STATE_DIE);*/
			SetState(FLYINGBOMB_STATE_THROWING_LEFT);

		}
	}

}

void CFlyingBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();
	x += vx * dt;
	/*x += vx * dt;*/
	/*if (x >= vW) {
		SetState(ID_ANI_FLYINGBOMB_FLYING_LEFT);
	}
	else if (x <= 0) {
		SetState(ID_ANI_FLYINGBOMB_FLYING_RIGHT);
	}*/
	if ((state == FLYINGBOMB_STATE_DIE) && (GetTickCount64() - die_start > FLYINGBOMB_STATE_DIE / 3))
	{
		isDeleted = true;

	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlyingBomb::Render()
{
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFlyingBomb::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLYINGBOMB_STATE_DIE:
		die_start = GetTickCount64();
	/*	aniId = FLYINGBOMB_STATE_DIE;*/
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case  FLYINGBOMB_STATE_FLYING_RIGHT :
		aniId = ID_ANI_FLYINGBOMB_FLYING_RIGHT;
		vx = FLYINGBOMB_FLYING_SPEED;
		nx = 1;
		ax = FLYINGBOMB_WALKING_ACCELERATION;
		break;
	case FLYINGBOMB_STATE_FLYING_LEFT:
		aniId =  ID_ANI_FLYINGBOMB_FLYING_LEFT;
		vx = -FLYINGBOMB_FLYING_SPEED;
		nx = -1;
		ax = -FLYINGBOMB_WALKING_ACCELERATION;
		break;
	case FLYINGBOMB_STATE_THROWING_LEFT:
		aniId = ID_ANI_FLYINGBOMB_THROWING_LEFT;
		vx = 0;
		vy = 0;
		break;
	}
}