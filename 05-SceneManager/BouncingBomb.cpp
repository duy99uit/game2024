
#include "BouncingBomb.h"
#include "Game.h"
CBouncingBomb::CBouncingBomb(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	SetState(BOUNCING_BOMB_STATE_FALLING);
	aniId = ID_ANI_BOUNCING_BOMB_FALLING;
}

void CBouncingBomb::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BOUNCING_BOMB_BBOX_WIDTH / 2;
	top = y - BOUNCING_BOMB_BBOX_HEIGHT / 2;
	right = left + BOUNCING_BOMB_BBOX_WIDTH;
	bottom = top + BOUNCING_BOMB_BBOX_HEIGHT;
}

void CBouncingBomb::OnNoCollision(DWORD dt)
{
};

void CBouncingBomb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();
	float vW = game->GetBackBufferWidth();


	CGameObject::Update(dt, coObjects);
}


void CBouncingBomb::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	/*RenderBoundingBox();*/
}

void CBouncingBomb::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	}
}