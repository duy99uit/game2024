#include "BeetleHead.h"
#include "Game.h"

CBeetleHead::CBeetleHead(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(BEETLEHEAD_STATE_WALKING_LEFT);
	aniId = ID_ANI_BEETLEHEAD_WALKING_LEFT;

	// Initialize sinusoidal movement parameters
	amplitude = 15.0f;   // Height of the wave
	frequency = 0.005f;  // Speed of oscillation
	phase = 0.0f;        // No initial offset
	baseY = y;           // Store the starting Y position as the base
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
	// Update vertical position using a sine wave
	float time = (float)GetTickCount64(); // Get current time in milliseconds
	y = baseY + amplitude * sin(frequency * time + phase);

	if ((state == BEETLEHEAD_STATE_DIE) && (GetTickCount64() - die_start > BEETLEHEAD_DIE_TIMEOUT / 3))
	{
		isDeleted = true;

	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
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