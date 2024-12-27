#include "PlatformWalker.h"
#include "Game.h"
#include "Platform.h"

CPlatformWalker::CPlatformWalker(float x, float y, int init_state, float px, float py, float cell_width, float cell_height, int length, int sprite_begin, int sprite_middle, int sprite_end) :CGameObject(x, y)
{
	die_start = -1;
	SetState(init_state);
//	aniId = ID_ANI_R_PLATFORMWALKER_STATE_WALKING_LEFT;
	CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	this->current_platform = new CPlatform(px, py, cell_width, cell_height,	length,	sprite_begin, sprite_middle, sprite_end);

	currentScene->AddObject(current_platform);
	//current_platform = nullptr;
}

void CPlatformWalker::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLATFORMWALKER_BBOX_WIDTH / 2;
	top = y - PLATFORMWALKER_BBOX_HEIGHT / 2;
	right = left + PLATFORMWALKER_BBOX_WIDTH;
	bottom = top + PLATFORMWALKER_BBOX_HEIGHT;
}

void CPlatformWalker::OnNoCollision(DWORD dt)
{
	if (current_platform != nullptr) {
		float p_left, p_right, p_top, p_bottom;
		current_platform->GetBoundingBox(p_left, p_top, p_right, p_bottom);
		//DebugOut(L"walker with platform p right %f , x = %f", p_right, x);
		if (x >= p_right + PLATFORMWALKER_BBOX_WIDTH/2)
			//if (x > 2015.000000)
		{
			//DebugOut(L"walker with platform");
			//SetState(R_PLATFORMWALKER_STATE_WALKING_DOWN);
			//theo chieu tu phai qua trai
			if (state == R_PLATFORMWALKER_STATE_WALKING_RIGHT && vx > 0) SetState(R_PLATFORMWALKER_STATE_WALKING_DOWN);
			if (state == R_PLATFORMWALKER_STATE_WALKING_DOWN && y <= p_bottom - PLATFORMWALKER_BBOX_HEIGHT/2 - PLATFORMWALKER_BBOX_HEIGHT) SetState(R_PLATFORMWALKER_STATE_WALKING_LEFT);

			//theo chieu tu trai sang phai
			if (state == L_PLATFORMWALKER_STATE_WALKING_RIGHT && vx > 0) SetState(L_PLATFORMWALKER_STATE_WALKING_UP);
			if (state == L_PLATFORMWALKER_STATE_WALKING_UP && y >= p_top + PLATFORMWALKER_BBOX_HEIGHT + PLATFORMWALKER_BBOX_HEIGHT / 2) SetState(L_PLATFORMWALKER_STATE_WALKING_LEFT);
		};

		if (x <= p_left - PLATFORMWALKER_BBOX_WIDTH / 2)
			{
				// theo chieu tu phai qua trai
				if (state == R_PLATFORMWALKER_STATE_WALKING_LEFT && vx < 0 ) SetState(R_PLATFORMWALKER_STATE_WALKING_UP);
				if (state == R_PLATFORMWALKER_STATE_WALKING_UP && y >= p_top + PLATFORMWALKER_BBOX_HEIGHT + PLATFORMWALKER_BBOX_HEIGHT / 2) SetState(R_PLATFORMWALKER_STATE_WALKING_RIGHT);

				// theo chieu tu trai sang phai
				if (state == L_PLATFORMWALKER_STATE_WALKING_LEFT && vx < 0) SetState(L_PLATFORMWALKER_STATE_WALKING_DOWN);
				if (state == L_PLATFORMWALKER_STATE_WALKING_DOWN && y <= p_bottom - PLATFORMWALKER_BBOX_HEIGHT / 2 - PLATFORMWALKER_BBOX_HEIGHT) SetState(L_PLATFORMWALKER_STATE_WALKING_RIGHT);
			}
	}
	x += vx * dt;
	y += vy * dt;
};

void CPlatformWalker::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();
	x += vx * dt;
	y += vy * dt;
	

	if ((state == PLATFORMWALKER_STATE_DIE) && (GetTickCount64() - die_start > PLATFORMWALKER_DIE_TIMEOUT / 3))
	{
		isDeleted = true;
		return;
	}


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPlatformWalker::OnCollisionWith(LPCOLLISIONEVENT e)
{
	DebugOut(L"cham platform");
	//if (!e->obj->IsBlocking()) return;
	/*if (dynamic_cast<CPlatform*>(e->obj)) {
		OnCollisionWithPlatform(e);
	}*/


}
void CPlatformWalker::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	current_platform = nullptr;
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);
	DebugOut(L"cham platform");
	current_platform = platform;
	//if (ny !=0 && state == R_PLATFORMWALKER_STATE_WALKING_DOWN) {
	//	if (ny > 0) {
	//		SetState(R_PLATFORMWALKER_STATE_WALKING_RIGHT);
	//	}
	//	else
	//	{
	//		SetState(R_PLATFORMWALKER_STATE_WALKING_LEFT);
	//	}
	//	
	//}



	//if (ny != 0 && state == L_PLATFORMWALKER_STATE_WALKING_DOWN) {
	//	if (ny > 0) {
	//		SetState(L_PLATFORMWALKER_STATE_WALKING_LEFT);
	//	}
	//	else
	//	{
	//		SetState(L_PLATFORMWALKER_STATE_WALKING_RIGHT);
	//	}

	//}

	
	
}

void CPlatformWalker::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPlatformWalker::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case L_PLATFORMWALKER_STATE_WALKING_LEFT:
		vx = - PLATFORMWALKER_WALKING_SPEED;
		vy = 0;
		aniId = ID_ANI_L_PLATFORMWALKER_STATE_WALKING_LEFT;
		break;

	case L_PLATFORMWALKER_STATE_WALKING_RIGHT:
		vx = PLATFORMWALKER_WALKING_SPEED;
		vy = 0;
		aniId = ID_ANI_L_PLATFORMWALKER_STATE_WALKING_RIGHT;
		break;

	case L_PLATFORMWALKER_STATE_WALKING_UP:
		vx = 0;
		vy = PLATFORMWALKER_WALKING_SPEED;
		aniId = ID_ANI_L_PLATFORMWALKER_STATE_WALKING_UP;
		break;
	case L_PLATFORMWALKER_STATE_WALKING_DOWN:
		vx = 0;
		vy = -PLATFORMWALKER_WALKING_SPEED;
		aniId = ID_ANI_L_PLATFORMWALKER_STATE_WALKING_DOWN;
		break;

	case R_PLATFORMWALKER_STATE_WALKING_LEFT:
		vx = -PLATFORMWALKER_WALKING_SPEED;
		vy = 0;
		aniId = ID_ANI_R_PLATFORMWALKER_STATE_WALKING_LEFT;
		break;

	case R_PLATFORMWALKER_STATE_WALKING_RIGHT:
		vx = PLATFORMWALKER_WALKING_SPEED;
		vy = 0;
		aniId = ID_ANI_R_PLATFORMWALKER_STATE_WALKING_RIGHT;
		break;

	case R_PLATFORMWALKER_STATE_WALKING_UP:
		vx = 0;
		vy = PLATFORMWALKER_WALKING_SPEED;
		aniId = ID_ANI_R_PLATFORMWALKER_STATE_WALKING_UP;
		break;
	case R_PLATFORMWALKER_STATE_WALKING_DOWN:
		vx = 0;
		vy = -PLATFORMWALKER_WALKING_SPEED;
		aniId = ID_ANI_R_PLATFORMWALKER_STATE_WALKING_DOWN;
		break;

	case PLATFORMWALKER_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	}
}
