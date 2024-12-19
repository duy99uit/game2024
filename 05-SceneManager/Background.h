#pragma once
#pragma once
#include "GameObject.h"
#include "Define.h"

#define ID_ANI_BACKGROUND 99999

//background
#pragma region backround
#define BACKGROUND_BBOX_WIDTH  16
#define BACKGROUND_BBOX_HEIGHT 16


class CBackground : public CGameObject
{
public:
	CBackground(float x, float y) : CGameObject(x, y) {}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
