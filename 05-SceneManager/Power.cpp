
#include "Power.h"
#include "Game.h"
CPower::CPower(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(POWER_STATE_IDLE);
	aniId = ID_ANI_POWER_IDLE;
}

void CPower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - POWER_BBOX_WIDTH / 2;
	top = y - POWER_BBOX_HEIGHT / 2;
	right = left + POWER_BBOX_WIDTH;
	bottom = top + POWER_BBOX_HEIGHT;
}

void CPower::OnNoCollision(DWORD dt)
{
};

void CPower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();
	

	CGameObject::Update(dt, coObjects);
}


void CPower::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	/*RenderBoundingBox();*/
}

void CPower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	
	}
}