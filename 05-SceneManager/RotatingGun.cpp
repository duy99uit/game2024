#include "RotatingGun.h"
#include "Game.h"
#include "PlayScene.h"

CRotatingGun::CRotatingGun(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(ROTATINGGUN_STATE_IDLE);
	aniId = ID_ANI_ROTATINGGUN_IDLE;
}

void CRotatingGun::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	boolean isShoot = state == ROTATINGGUN_STATE_SHOOT;
	if (isShoot) {
		left = x - ROTATINGGUN_BBOX_WIDTH / 2;
		top = y - ROTATINGGUN_BBOX_HEIGHT / 2;
		right = left + ROTATINGGUN_BBOX_WIDTH;
		bottom = top + ROTATINGGUN_BBOX_HEIGHT;
	}
	else {
		left = x - ROTATINGGUN_BBOX_WIDTH_IDLE / 2;
		top = y - ROTATINGGUN_BBOX_HEIGHT_IDLE / 2;
		right = left + ROTATINGGUN_BBOX_WIDTH_IDLE;
		bottom = top + ROTATINGGUN_BBOX_HEIGHT_IDLE;
	}
	
}

void CRotatingGun::OnNoCollision(DWORD dt)
{
};

void CRotatingGun::OnCollisionWith(LPCOLLISIONEVENT e)

{
	DebugOut(L"CRotatingGun::OnCollisionWith 22222");
	if (dynamic_cast<CSophia*>(e->obj)) {
		OnCollisionWithSophia(e);
	}


}

void CRotatingGun::OnCollisionWithSophia(LPCOLLISIONEVENT e)
{
	CSophia* sophia = dynamic_cast<CSophia*>(e->obj);

		if (sophia->GetState() != SOPHIA_STATE_DIE && state != ROTATINGGUN_STATE_SHOOT)
		{
			SetState(ROTATINGGUN_STATE_SHOOT);

		}
	

}

void CRotatingGun::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	if ((state == ROTATINGGUN_STATE_DIE) && (GetTickCount64() - die_start > ROTATINGGUN_DIE_TIMEOUT / 3))
	{
		isDeleted = true;

	}
	/*if ((state == FLYINGBOMB_STATE_THROWING_LEFT) && (GetTickCount64() - prepareEscape_start > FLYINGBOMB_PREPARE_ESCAP_TIME))
	{
		SetState(FLYINGBOMB_STATE_ESCAPING_LEFT);


	}*/
	CCollision::GetInstance()->Process(this, dt, coObjects);
}



void CRotatingGun::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CRotatingGun::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ROTATINGGUN_STATE_DIE:
		die_start = GetTickCount64();
		break;
	case ROTATINGGUN_STATE_IDLE:
		aniId = ID_ANI_ROTATINGGUN_IDLE;
		break;
	case ROTATINGGUN_STATE_SHOOT:
		aniId = ID_ANI_ROTATINGGUN_SHOOT;
		break;
	}
}
