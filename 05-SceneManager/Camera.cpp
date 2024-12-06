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

void Camera::Update(float player_x, float player_y)
{


	CGame* game = CGame::GetInstance();
	if (player_x > width / 2 and player_x < width + 100 ) {
		cam_x = player_x - width / 2;
	}

	//DebugOut(L"[WARNING]  playser y  %f already exists\n", player_y);

	if  (player_y < (height - 30) and player_y > 30) {
		cam_y = player_y + height / 2;
	}


	CGame::GetInstance()->SetCamPos(cam_x, cam_y);
}

void  Camera::TransPosition(float& x, float& y)

{
	//DebugOut(L"[WARNING] trán cam_y  %f already exists\n", cam_y);
	x = x - cam_x;
	y = height + y - cam_y ;

}