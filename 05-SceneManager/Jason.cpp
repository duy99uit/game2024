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
   DebugOut(L"Dang o dau >>>>> %f %f \n", x, y);
}

void CJason::OnCollisionWith(LPCOLLISIONEVENT e)
{
}



void CJason::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	
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
		aniId = ID_ANI_BIG_JASON_WALKING_RIGHT;
		vx = BIG_JASON_WALKING_SPEED;
		nx = 1;
		break;
	case BIG_JASON_STATE_WALKING_LEFT:
		aniId = ID_ANI_BIG_JASON_WALKING_LEFT;
		vx = -BIG_JASON_WALKING_SPEED;
		nx = -1;
		break;

	case BIG_JASON_STATE_WALKING_UP:
		aniId = ID_ANI_BIG_JASON_WALKING_UP;
		vy = BIG_JASON_WALKING_SPEED;
		ny = 1;
		break;
	case BIG_JASON_STATE_WALKING_DOWN:
		aniId = ID_ANI_BIG_JASON_WALKING_DOWN;
		vy = -BIG_JASON_WALKING_SPEED;
		ny = -1;
		break;
	case BIG_JASON_STATE_IDLE_LEFT:
		aniId = ID_ANI_BIG_JASON_IDLE_LEFT;
		nx = -1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case BIG_JASON_STATE_IDLE_RIGHT:
		aniId = ID_ANI_BIG_JASON_IDLE_RIGHT;
		nx = 1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case BIG_JASON_STATE_IDLE_UP:
		aniId = ID_ANI_BIG_JASON_IDLE_UP;
		ny = -1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case BIG_JASON_STATE_IDLE_DOWN:
		aniId = ID_ANI_BIG_JASON_IDLE_DOWN;
		ny = 1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case SMALL_JASON_STATE_WALKING_RIGHT:
		aniId = ID_ANI_SMALL_JASON_WALKING_RIGHT;
		vx = BIG_JASON_WALKING_SPEED;
		nx = 1;
		break;
	case SMALL_JASON_STATE_WALKING_LEFT:
		aniId = ID_ANI_SMALL_JASON_WALKING_LEFT;
		vx = -BIG_JASON_WALKING_SPEED;
		nx = -1;
		break;
	case SMALL_JASON_STATE_CLIMBING_UP:
		aniId = ID_ANI_SMALL_JASON_CLIMBING;
		vy = BIG_JASON_WALKING_SPEED;
		ny = 1;
		break;
	case SMALL_JASON_STATE_CLIMBING_DOWN:
		aniId = ID_ANI_SMALL_JASON_CLIMBING;
		vy = -BIG_JASON_WALKING_SPEED;
		ny = -1;
		break;
	case SMALL_JASON_STATE_IDLE_LEFT:
		aniId = ID_ANI_SMALL_JASON_IDLE_LEFT;
		nx = -1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case SMALL_JASON_STATE_IDLE_RIGHT:
		aniId = ID_ANI_SMALL_JASON_IDLE_RIGHT;
		nx = 1;
		ax = 0.0f;
		vx = 0.0f;
		ay = 0.0f;
		vy = 0.0f;
		break;
	case SMALL_JASON_STATE_CRAWLING_RIGHT:
		aniId = ID_ANI_SMALL_JASON_CRAWLING_RIGHT;
		vx = BIG_JASON_CRAWLING_SPEED;
		nx = 1;
		break;
	case SMALL_JASON_STATE_SWIMMING_RIGHT:
		aniId = ID_ANI_SMALL_JASON_SWMMING_RIGHT;
		vx = BIG_JASON_CRAWLING_SPEED;
		nx = 1;
		break;
	case SMALL_JASON_STATE_CRAWLING_LEFT:
		aniId = ID_ANI_SMALL_JASON_CRAWLING_LEFT;
		vx = -BIG_JASON_CRAWLING_SPEED;
		nx = -1;
		break;
	case SMALL_JASON_STATE_SWIMMING_LEFT:
		aniId = ID_ANI_SMALL_JASON_SWMMING_LEFT;
		vx = -BIG_JASON_CRAWLING_SPEED;
		nx =-1;
		break;
	case BIG_JASON_STATE_IDLE:
		aniId = ID_ANI_BIG_JASON_IDLE_RIGHT;
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
	if (level == JASON_LEVEL_BIG) {
		switch (KeyCode)
		{
		case DIK_UP:
			SetState(BIG_JASON_STATE_IDLE_UP);
			break;
		case DIK_DOWN:
			
			SetState(BIG_JASON_STATE_IDLE_DOWN);
			break;
		case DIK_LEFT:
			
			SetState(BIG_JASON_STATE_IDLE_LEFT);
			break;
		case DIK_RIGHT:
		
			SetState(BIG_JASON_STATE_IDLE_RIGHT);
			break;
		}
	}
	else {
		switch (KeyCode)
		{
		case DIK_UP:
			SetState(SMALL_JASON_STATE_IDLE_RIGHT);
			break;
		case DIK_DOWN:
			SetState(SMALL_JASON_STATE_IDLE_RIGHT);
			break;
		case DIK_LEFT:
			SetState(SMALL_JASON_STATE_IDLE_LEFT);
			break;
		case DIK_RIGHT:
			SetState(SMALL_JASON_STATE_IDLE_RIGHT);
			break;
		case DIK_A:
			SetState(SMALL_JASON_STATE_IDLE_LEFT);
			break;
		case DIK_S:
			SetState(SMALL_JASON_STATE_IDLE_RIGHT);
			break;
		case DIK_D:
			SetState(SMALL_JASON_STATE_IDLE_LEFT);
			break;
		case DIK_F:
			SetState(SMALL_JASON_STATE_IDLE_LEFT);
			break;
		}
	}
	

}
void CJason::HandleKeyDown(int KeyCode)

{
	int state = getState();
	if (level == JASON_LEVEL_BIG) {
		switch (KeyCode)
		{
		case DIK_1:
			SetState(SMALL_JASON_STATE_IDLE_RIGHT);
			SetLevel(JASON_LEVEL_SMALL);
			break;
		case DIK_RIGHT:
			SetState(BIG_JASON_STATE_WALKING_RIGHT);
			break;
		case DIK_LEFT:
			SetState(BIG_JASON_STATE_WALKING_LEFT);
			break;
		case DIK_UP:
			SetState(BIG_JASON_STATE_WALKING_UP);
			break;
		case DIK_DOWN:
			SetState(BIG_JASON_STATE_WALKING_DOWN);
			break;
		}
	}
	else {
		switch (KeyCode)
		{
		case DIK_1:
			SetState(BIG_JASON_STATE_IDLE_RIGHT);
			SetLevel(JASON_LEVEL_BIG);
			break;
		case DIK_RIGHT:
			SetState(SMALL_JASON_STATE_WALKING_RIGHT);
			break;
		case DIK_LEFT:
			SetState(SMALL_JASON_STATE_WALKING_LEFT);
			break;
		case DIK_UP:
			SetState(SMALL_JASON_STATE_CLIMBING_UP);
			break;
		case DIK_DOWN:
			SetState(SMALL_JASON_STATE_CLIMBING_DOWN);
			break;
		case DIK_A:
			SetState(SMALL_JASON_STATE_CRAWLING_LEFT);
			break;
		case DIK_S:
			SetState(SMALL_JASON_STATE_SWIMMING_LEFT);
			break;
		case DIK_F:
			SetState(SMALL_JASON_STATE_CRAWLING_RIGHT);
			break;
		case DIK_D:
			SetState(SMALL_JASON_STATE_SWIMMING_RIGHT);
			break;
		}
	}
	
}


