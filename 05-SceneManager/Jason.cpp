#include <algorithm>
#include "debug.h"

#include "Jason.h"
#include "Game.h"

#include "BlackWalker.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"

void CJason::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	/*vy += ay * dt;*/
	/*vx += ax * dt;*/


vx += ax * dt;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CJason::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
//	DebugOut(L"OnNoCollision >>>>> %d\n", x, vx);
}

void CJason::OnCollisionWith(LPCOLLISIONEVENT e)
{
}



int CJason::GetAniIdBig()
{
	int aniId = -1;
	if (vy != 0) {
		if (vy < 0) {
			aniId = ID_ANI_JASON_WALKING_DOWN;
		}
		else {
			aniId = ID_ANI_JASON_WALKING_UP;
		}
	}
	else if (vx != 0) {
		if (vx > 0) {
			aniId = ID_ANI_JASON_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_JASON_WALKING_LEFT;
		}
	}
	else {
		if (!isMovingX) { 
			if (ny > 0) {
				aniId = ID_ANI_JASON_IDLE_DOWN;
			}
			else if (ny < 0) {
				aniId = ID_ANI_JASON_IDLE_UP;
			}
		}
		else {
			if (nx > 0) {
				aniId = ID_ANI_JASON_IDLE_RIGHT;
			}
			else {
				aniId = ID_ANI_JASON_IDLE_LEFT;
			}
		}
	}
	if (aniId == -1) aniId = ID_ANI_JASON_IDLE_RIGHT;

	return aniId;
}


void CJason::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	aniId = GetAniIdBig();;
	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
	DebugOutTitle(L"Blaster Master: %d");
}


void CJason::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == JASON_STATE_DIE) return; 

	switch (state)
	{
	case JASON_STATE_WALKING_RIGHT:
		vx = JASON_WALKING_SPEED;
		nx = 1;
		isMovingX = true;
		break;
	case JASON_STATE_WALKING_LEFT:
		vx = -JASON_WALKING_SPEED;
		nx = -1;
		isMovingX = true;
		break;

	case JASON_STATE_WALKING_UP:
		vy = JASON_WALKING_SPEED;
		ny = 1;
		isMovingX = false;
		break;
	case JASON_STATE_WALKING_DOWN:
		vy = -JASON_WALKING_SPEED;
		ny = -1;
		isMovingX = false;
		break;


	case JASON_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	}

	CGameObject::SetState(state);
}

void CJason::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==JASON_LEVEL_BIG)
	{
			left = x - JASON_BIG_BBOX_WIDTH/2;
			top = y - JASON_BIG_BBOX_HEIGHT/2;
			right = left + JASON_BIG_BBOX_WIDTH;
			bottom = top + JASON_BIG_BBOX_HEIGHT;
	}
	else
	{
		left = x - JASON_SMALL_BBOX_WIDTH/2;
		top = y - JASON_SMALL_BBOX_HEIGHT/2;
		right = left + JASON_SMALL_BBOX_WIDTH;
		bottom = top + JASON_SMALL_BBOX_HEIGHT;
	}
}

void CJason::SetLevel(int l)
{
	level = l;
}




void CJason::HandleKeyState(BYTE* states)
{
	// remove key state
	LPGAME game = CGame::GetInstance();

	/*player->GetPosition(cx, cy);*/


	if (game->IsKeyDown(DIK_RIGHT))
	{
		SetState(JASON_STATE_WALKING_RIGHT);
		
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		SetState(JASON_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_UP))
	{
		SetState(JASON_STATE_WALKING_UP);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		SetState(JASON_STATE_WALKING_DOWN);
	}
	else
	{
		SetState(JASON_STATE_IDLE);
	}
}


