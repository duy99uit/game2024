
#include <algorithm>
#include "debug.h"

#include "Jason.h"
#include "Sophia.h"
#include "Game.h"

#include "BlackWalker.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "BlackWalker.h"
#include "PlayScene.h"

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	vy += -ay * dt;
	vx += ax * dt;
	/*isOnPlatform = true;*/

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (vy > 0) {
		/*vy -= SOPHIA_JUMP_SPEED_Y/3;*/
	}



	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSophia::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	/*isOnPlatform = false;*/
	DebugOut(L"OnNoCollision >>>>> %d\n", x, vx);
}

void CSophia::OnCollisionWith(LPCOLLISIONEVENT e)
{
	DebugOut(L"CSophia::OnCollisionWith 11111");
	
	
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		DebugOut(L"CSophia::OnCollisionWith 1111");
		vy = 0;
		isOnPlatform = true;
	}
	//else
	//{

	//}

	if (dynamic_cast<CBlackWalker*>(e->obj)) {
		OnCollisionWithBlackWalker(e);
	}
		
}
void CSophia::OnCollisionWithBlackWalker(LPCOLLISIONEVENT e)
{
	CBlackWalker* blackWalker = dynamic_cast<CBlackWalker*>(e->obj);
	DebugOut(L"CSophia::OnCollisionWith 22223");
	if (e->nx != 0 || e-> ny !=0)
	{
		if (blackWalker->GetState() != BLACKWALKER_STATE_DIE)
		{
			blackWalker->SetState(BLACKWALKER_STATE_DIE);

		}
	}
	isOnPlatform = true;
}




void CSophia::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
	DebugOutTitle(L"Blaster Master: %d");
}


void CSophia::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOPHIA_STATE_DIE:
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case SOPHIA_STATE_OPEN_LEFT:
		aniId = ID_ANI_SOPHIA_OPEN_LEFT;
		vx = 0;
		vy = 0;
		ay = 0;
		nx = -1;
		break;
	case SOPHIA_STATE_OPEN_RIGHT:
		aniId = ID_ANI_SOPHIA_OPEN_RIGHT;
		vx = 0;
		vy = 0;
		ay = 0;
		nx = 1;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		aniId = ID_ANI_SOPHIA_WALKING_LEFT;
		maxVx = -SOPHIA_WALKING_SPEED;
		vx = -SOPHIA_WALKING_SPEED;
		ax = -SOPHIA_WALKING_ACCELERATION;
		nx = -1;
		break;
	case SOPHIA_STATE_WALKING_RIGHT:
		maxVx = SOPHIA_WALKING_SPEED;
		aniId = ID_ANI_SOPHIA_WALKING_RIGHT;
		vx = SOPHIA_WALKING_SPEED;
		ax = SOPHIA_WALKING_ACCELERATION;
		nx = 1;
		break;
	case SOPHIA_STATE_IDLE_LEFT:
		aniId = ID_ANI_SOPHIA_WALKING_LEFT;
		nx = -1;
		ax = 0.0f;
		vx = 0.0f;
		break;
	case SOPHIA_STATE_IDLE_RIGHT:
		aniId = ID_ANI_SOPHIA_WALKING_RIGHT;
		nx = 1;
		ax = 0.0f;
		vx = 0.0f;
		break;
	case SOPHIA_STATE_JUMP_RIGHT:
		aniId = ID_ANI_SOPHIA_JUMP_RIGHT;
		ay = -0.0025f;
		vy = -0.001f;
		break;
	case SOPHIA_STATE_JUMP_LEFT:
		aniId = ID_ANI_SOPHIA_JUMP_LEFT;
		ay = -0.0025f;
		vy = -0.001f;
		break;
	case SOPHIA_STATE_FALLING_LEFT:
		aniId = ID_ANI_SOPHIA_FALLING_LEFT;
		ay = 0.0025f/3;
		vy = 0.001f;
		break;
	case SOPHIA_STATE_FALLING_RIGHT:
		aniId = ID_ANI_SOPHIA_FALLING_RIGHT;
		ay = 0.0025f/3;
		vy = 0.001f;
		break;
	case SOPHIA_STATE_SHOOT_TOP_LEFT:
		aniId = ID_ANI_SOPHIA_SHOOT_TOP_LEFT;
		break;
	case SOPHIA_STATE_SHOOT_TOP_RIGHT:
		aniId = ID_ANI_SOPHIA_SHOOT_TOP_RIGHT;
		break;
	case SOPHIA_STATE_SHOOT_DIAGONAL_LEFT:
		aniId = ID_ANI_SOPHIA_SHOOT_DIAGONAL_LEFT;
		break;
	case SOPHIA_STATE_SHOOT_DIAGONAL_RIGHT:
		aniId = ID_ANI_SOPHIA_SHOOT_DIAGONAL_RIGHT;
		break;
	}
}


void CSophia::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SOPHIA_BBOX_WIDTH / 2;
	top = y - SOPHIA_BBOX_HEIGHT / 2;
	right = left + SOPHIA_BBOX_WIDTH;
	bottom = top + SOPHIA_BBOX_HEIGHT;
}

void CSophia::SetLevel(int l)
{
	level = l;
}




void CSophia::HandleKeyState()
{
	LPGAME game = CGame::GetInstance();
}

void CSophia::HandleKeyUp(int KeyCode)
{
	boolean isLeftDirection = nx < 0;
	switch (KeyCode)
	{
	case DIK_LEFT:

		SetState(SOPHIA_STATE_IDLE_LEFT);
		break;
	case DIK_RIGHT:

		SetState(SOPHIA_STATE_IDLE_RIGHT);
		break;
	case DIK_S:
		if (state == SOPHIA_STATE_JUMP_RIGHT) {
			SetState(SOPHIA_STATE_FALLING_RIGHT);
		}
		else {
			SetState(SOPHIA_STATE_FALLING_LEFT);
		}
		
		isOnPlatform = false;
		break;
	}
	


}
void CSophia::HandleKeyDown(int KeyCode)

{
	boolean isLeftDirection = nx < 0;
	switch (KeyCode)
	{
	case DIK_RIGHT:
		
		SetState(SOPHIA_STATE_WALKING_RIGHT);
		break;
	case DIK_LEFT:
		
		SetState(SOPHIA_STATE_WALKING_LEFT);
		break;
	case DIK_S:
		if (isOnPlatform) {
			if (isLeftDirection) {
				SetState(SOPHIA_STATE_JUMP_LEFT);
			}
			else {
				SetState(SOPHIA_STATE_JUMP_RIGHT);
			}
			
		}
		
		break;
	case DIK_Z:

		if (isLeftDirection) {
			SetState(SOPHIA_STATE_OPEN_LEFT);
		}
		else {
			SetState(SOPHIA_STATE_OPEN_RIGHT);
		}
		break;
	case DIK_X:
		if (isLeftDirection) {
			SetState(SOPHIA_STATE_SHOOT_TOP_LEFT);
		}
		else {
			SetState(SOPHIA_STATE_SHOOT_TOP_RIGHT);
		}
		break;
	case DIK_C:
		if (isLeftDirection) {
			SetState(SOPHIA_STATE_SHOOT_DIAGONAL_LEFT);
		}
		else {
			SetState(SOPHIA_STATE_SHOOT_DIAGONAL_RIGHT);
		}
		break;
	case DIK_SPACE:

		Shoot();
		break;
	}

}

void CSophia::Shoot() {
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	boolean isLeftDirection = nx < 0;
	float xbullet = isLeftDirection ? x - SOPHIA_BBOX_WIDTH / 2 : x + SOPHIA_BBOX_WIDTH / 2;
	float ybullet = y + SOPHIA_BBOX_HEIGHT / 4;
	float vxBullet = isLeftDirection ? -BULLET_SPEED_X : BULLET_SPEED_X;
	float vyBullett = 0.0f;
	this->bullet = new SophiaBullet(xbullet, ybullet, vxBullet, vyBullett);
	currentScene->AddObject(bullet);
}



