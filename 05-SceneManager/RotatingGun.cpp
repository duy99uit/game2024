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
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CGameObject* player = currentScene->GetPlayer();
	float player_x, player_y;
	player->GetPosition(player_x, player_y);
	// && (GetTickCount64() - shoot_start > ROTATINGGUN_RELOAD_BULLET_TIME
	if (state == ROTATINGGUN_STATE_SHOOT && (GetTickCount64() - shoot_start > ROTATINGGUN_RELOAD_BULLET_TIME)) {
		if (abs(player_x - x) <= ROTATINGGUN_DISTANCE_SHOOT_NEAR)
		{
			if (player_x <= x)
			{
				RotatingBullet* bullet = new RotatingBullet(x, y, -ROTATINGGUN_SPEED_SHOOT_NEAR_X, - ROTATINGGUN_SPEED_SHOOT_NEAR_Y);
				currentScene->AddObject(bullet);
				DebugOut(L"CRotatingGun ban gan ben trai");
			}
			else
			{
				RotatingBullet* bullet = new RotatingBullet(x, y, ROTATINGGUN_SPEED_SHOOT_NEAR_X, -ROTATINGGUN_SPEED_SHOOT_NEAR_Y);
				currentScene->AddObject(bullet);
				DebugOut(L"CRotatingGun ban gan ben phai");
			}
			
		}
		else
		{
			if (player_x <= x)
			{
				RotatingBullet* bullet = new RotatingBullet(x, y, -ROTATINGGUN_SPEED_SHOOT_FAR_X, -ROTATINGGUN_SPEED_SHOOT_FAR_Y);
				currentScene->AddObject(bullet);
				DebugOut(L"CRotatingGun ban xa ben trai");
			}
			else
			{
				RotatingBullet* bullet = new RotatingBullet(x, y, ROTATINGGUN_SPEED_SHOOT_FAR_X, -ROTATINGGUN_SPEED_SHOOT_FAR_Y);
				currentScene->AddObject(bullet);
				DebugOut(L"CRotatingGun ban xa ben phai");
			}
		}
		
		shoot_start = GetTickCount64();
	}

};

void CRotatingGun::OnCollisionWith(LPCOLLISIONEVENT e)

{
	//DebugOut(L"CRotatingGun::OnCollisionWith 22222");
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
			CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			CGameObject* player = currentScene->GetPlayer();
			RotatingBullet* bullet1 = new RotatingBullet(x, y, -ROTATINGGUN_SPEED_SHOOT_NEAR_X, -ROTATINGGUN_SPEED_SHOOT_NEAR_Y);
			currentScene->AddObject(bullet1);
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
		shoot_start = GetTickCount64();
		aniId = ID_ANI_ROTATINGGUN_IDLE;
		break;
	case ROTATINGGUN_STATE_SHOOT:
		aniId = ID_ANI_ROTATINGGUN_SHOOT;
		break;
	}
}
