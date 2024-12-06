
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

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	/*vy += ay * dt;
	vx += ax * dt;*/

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
	
	
	//if (e->ny != 0 && e->obj->IsBlocking())
	//{
	//	DebugOut(L"CSophia::OnCollisionWith 1111");
	//	/*vy = 0;*/
	//	/*isOnPlatform = true;*/
	//}
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
	// jump on top >> kill Goomba and deflect a bit 
	if (e->nx != 0)
	{
		blackWalker->SetState(BLACKWALKER_STATE_DIE);
	}
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
		ay = 0.0f;
		vy = 0.0f;
		break;
	case SOPHIA_STATE_IDLE_RIGHT:
		aniId = ID_ANI_SOPHIA_WALKING_RIGHT;
		nx = 1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case SOPHIA_STATE_JUMP:
		/*DebugOut(L"[WARNING] SOPHIA_STATE_JUMP  %f already exists\n", isOnPlatform);
		if (isOnPlatform)
		{
			if (abs(this->vy) == SOPHIA_WALKING_SPEED)
				ay = -SOPHIA_GRAVITY;
			else
				vy = SOPHIA_JUMP_SPEED_Y;
		}*/
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
	switch (KeyCode)
	{
	case DIK_LEFT:

		SetState(SOPHIA_STATE_IDLE_LEFT);
		break;
	case DIK_RIGHT:

		SetState(SOPHIA_STATE_IDLE_RIGHT);
		break;
	}


}
void CSophia::HandleKeyDown(int KeyCode)

{
	switch (KeyCode)
	{
	case DIK_RIGHT:
		SetState(SOPHIA_STATE_WALKING_RIGHT);
		break;
	case DIK_LEFT:
		SetState(SOPHIA_STATE_WALKING_LEFT);
		break;
	case DIK_S:
		SetState(SOPHIA_STATE_JUMP);
		break;
	}

}


