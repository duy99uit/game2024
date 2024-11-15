#include "Camera.h"
#include "Game.h"
#include "debug.h"

void Camera::SetCamPos(float x, float y)
{
	cam_x = x; cam_y = y;
}
void Camera::SetSize(float w, float h)
{
	width = w; height = h;
}
float Camera::getCamPosY()
{
	return cam_y;
}
float Camera::getCamPosX()
{
	return cam_x;
}
void Camera::Update(float player_x, float player_y)
{


	CGame* game = CGame::GetInstance();
	DebugOut(L"[WARNING] cam_x  %f already exists\n", cam_x);
	//DebugOut(L"[WARNING] cam_y  %f already exists\n", cam_y);

	//DebugOut(L"[WARNING] GetBackBufferWidth()  %d already exists\n", game->GetBackBufferWidth());
	//DebugOut(L"[WARNING] game->GetBackBufferHeight()  %d already exists\n", game->GetBackBufferHeight());
	if (player_x > width / 2 and player_x < width + 100 ) {
		cam_x = player_x - width / 2;
	}

	if (player_y < height and player_y > 30) {
		cam_y = player_y - height / 2;
	}
	// them dieu kien check bien x ben trai, x ben phai
	

	CGame::GetInstance()->SetCamPos(cam_x, cam_y);
}

void  Camera::TransPosition(float& x, float& y)
{
	x = x - cam_x;
	y = y - cam_y;
}