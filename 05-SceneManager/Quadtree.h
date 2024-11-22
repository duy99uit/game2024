#pragma once
#include <iostream>
#include <fstream>;
#include "Utils.h"
#include "GameObject.h"
#include "Define.h"
using namespace std;
class Rect
{
public:
	double x;
	double y;
	float width;
	Rect() { this->x = 0; this->y = 0; this->width = MAX_WIDTH_OF_QUADTREE; }
	Rect(double x, double y) { this->x = x; this->y = y; this->width = MAX_WIDTH_OF_QUADTREE; }
	Rect(double x, double y, float width) { this->x = x; this->y = y; this->width = width; }
};
class Quadtree
{
	vector<LPGAMEOBJECT> object;
	Quadtree* topLeftTree;
	Quadtree* topRightTree;
	Quadtree* botLeftTree;
	Quadtree* botRightTree;
	int level;
	Rect size;
public:
	Quadtree();
	Quadtree(int level, double x, double y, float width);
	Quadtree(LPCWSTR path);
	void AddObject(LPGAMEOBJECT obj);
	void Split();
	bool inBoundary(double x, double y);
	void _ParseSection_OBJECTS_QT(string line);
	vector<LPGAMEOBJECT> getAllObjectInQT() { return object; }
};

