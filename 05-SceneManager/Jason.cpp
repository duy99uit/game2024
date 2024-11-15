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
	DebugOut(L"OnNoCollision >>>>> %d\n", x, vx);
}

void CJason::OnCollisionWith(LPCOLLISIONEVENT e)
{
}



int CJason::GetAniIdBig()
{
	int aniId = -1;
	switch (state)
	{
	case BIG_JASON_STATE_WALKING_RIGHT:
		aniId = ID_ANI_BIG_JASON_WALKING_RIGHT;
		break;
	case BIG_JASON_STATE_WALKING_LEFT:
		aniId = ID_ANI_BIG_JASON_WALKING_LEFT;
		break;
	case BIG_JASON_STATE_WALKING_UP:
		aniId = ID_ANI_BIG_JASON_WALKING_UP;
		break;
	case BIG_JASON_STATE_WALKING_DOWN:
		aniId = ID_ANI_BIG_JASON_WALKING_DOWN;
		break;
	case BIG_JASON_STATE_IDLE_LEFT:
		aniId = ID_ANI_BIG_JASON_IDLE_LEFT;
		break;
	case BIG_JASON_STATE_IDLE_RIGHT:
		aniId = ID_ANI_BIG_JASON_IDLE_RIGHT;
		break;
	case BIG_JASON_STATE_IDLE_UP:
		aniId = ID_ANI_BIG_JASON_IDLE_UP;
		break;
	case BIG_JASON_STATE_IDLE_DOWN:
		aniId = ID_ANI_BIG_JASON_IDLE_DOWN;
		break;
	default:
		aniId = ID_ANI_BIG_JASON_IDLE_RIGHT;
		break;
	}
	if (aniId == -1) aniId = ID_ANI_BIG_JASON_IDLE_RIGHT;

	return aniId;
}

int CJason::GetAniIdSmall()
{
	int aniId = -1;
	switch (state)
	{
	case SMALL_JASON_STATE_WALKING_RIGHT:
		aniId = ID_ANI_SMALL_JASON_WALKING_RIGHT;
		break;
	case SMALL_JASON_STATE_WALKING_LEFT:
		aniId = ID_ANI_SMALL_JASON_WALKING_LEFT;
		break;
	case SMALL_JASON_STATE_WALKING_UP:
		aniId = ID_ANI_SMALL_JASON_WALKING_UP;
		break;
	case SMALL_JASON_STATE_WALKING_DOWN:
		aniId = ID_ANI_SMALL_JASON_WALKING_DOWN;
		break;
	case SMALL_JASON_STATE_IDLE_LEFT:
		aniId = ID_ANI_SMALL_JASON_IDLE_LEFT;
		break;
	case SMALL_JASON_STATE_IDLE_RIGHT:
		aniId = ID_ANI_SMALL_JASON_IDLE_RIGHT;
		break;
	case SMALL_JASON_STATE_IDLE_UP:
		aniId = ID_ANI_SMALL_JASON_IDLE_UP;
		break;
	case SMALL_JASON_STATE_IDLE_DOWN:
		aniId = ID_ANI_SMALL_JASON_IDLE_DOWN;
		break;
	default:
		aniId = ID_ANI_SMALL_JASON_IDLE_RIGHT;
		break;
	}
	if (aniId == -1) aniId = ID_ANI_SMALL_JASON_IDLE_RIGHT;

	return aniId;
}

void CJason::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	aniId = GetAniIdSmall();;
	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
	DebugOutTitle(L"Blaster Master: %d");
}


void CJason::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == BIG_JASON_STATE_DIE) return; 

	switch (state)
	{
	case BIG_JASON_STATE_WALKING_RIGHT:
		vx = BIG_JASON_WALKING_SPEED;
		nx = 1;
		isMovingX = true;
		break;
	case BIG_JASON_STATE_WALKING_LEFT:
		vx = -BIG_JASON_WALKING_SPEED;
		nx = -1;
		isMovingX = true;
		break;

	case BIG_JASON_STATE_WALKING_UP:
		vy = -BIG_JASON_WALKING_SPEED;
		ny = -1;
		isMovingX = false;
		break;
	case BIG_JASON_STATE_WALKING_DOWN:
		vy = BIG_JASON_WALKING_SPEED;
		ny = 1;
		isMovingX = false;
		break;
	case BIG_JASON_STATE_IDLE_LEFT:
		nx = -1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case BIG_JASON_STATE_IDLE_RIGHT:
		nx = 1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case BIG_JASON_STATE_IDLE_UP:
		ny = -1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case BIG_JASON_STATE_IDLE_DOWN:
		ny = 1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;


	case BIG_JASON_STATE_IDLE:
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




void CJason::HandleKeyState()
{
	LPGAME game = CGame::GetInstance();
}

void CJason::HandleKeyUp(int KeyCode)
{
	
	switch (KeyCode)
	{
	case DIK_UP:
		DebugOut(L"HandleKeyUp up >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_IDLE_UP);
		break;
	case DIK_DOWN:
		DebugOut(L"HandleKeyUp down >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_IDLE_DOWN);
		break;
	case DIK_LEFT:
		DebugOut(L"HandleKeyUp up >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_IDLE_LEFT);
		break;
	case DIK_RIGHT:
		DebugOut(L"HandleKeyUp up >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_IDLE_RIGHT);
		break;
	}
}
void CJason::HandleKeyDown(int KeyCode)
{
	int state = getState();
	switch (KeyCode)
	{
	case DIK_RIGHT:
		DebugOut(L"HandleKeyUp up >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_WALKING_RIGHT);
		break;
	case DIK_LEFT:
		DebugOut(L"HandleKeyUp up >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_WALKING_LEFT);
		break;
	case DIK_UP:
		DebugOut(L"HandleKeyUp up >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_WALKING_UP);
		break;
	case DIK_DOWN:
		DebugOut(L"HandleKeyUp down >>>>> %d\n", state);
		SetState(BIG_JASON_STATE_WALKING_DOWN);
		break;
	}
}


