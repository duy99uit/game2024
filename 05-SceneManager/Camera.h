#pragma once
class Camera
{
	float cam_x = 0.0f;
	float cam_y = 0.0f;
	float width;
	float height;
public:
	void SetSize(float w, float h);
	void SetCamPos(float x, float y);
	void Update(float player_x, float player_y);
	void TransPosition(float& x, float& y);
};