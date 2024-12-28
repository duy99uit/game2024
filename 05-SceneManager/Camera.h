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
	void GetCamInfo(float& cam_x, float& cam_y, float& width, float& height) { cam_x = this->cam_x; cam_y = this->cam_y; width = this->width, height = this->height; }
};