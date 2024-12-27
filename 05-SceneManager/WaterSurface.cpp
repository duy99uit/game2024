#include "WaterSurface.h"
#include "Game.h"
#include "debug.h"

CWaterSurface::CWaterSurface(float x, float y) :CGameObject(x, y)
{
	die_start = -1;
	aniId = ID_ANI_WATERSURFACE;
}

void CWaterSurface::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x ;
	top = y ;
	right = left + WATERSURFACE_BBOX_WIDTH;
	bottom = top + WATERSURFACE_BBOX_HEIGHT;
}

void CWaterSurface::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CWaterSurface::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGame* game = CGame::GetInstance();

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CWaterSurface::OnCollisionWith(LPCOLLISIONEVENT e)
{

}


void CWaterSurface::Render()
{

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CWaterSurface::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{

	}
}
