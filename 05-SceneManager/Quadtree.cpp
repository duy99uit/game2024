#include "Quadtree.h"
#include "debug.h"
#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Platform.h"

#include "SampleKeyEventHandler.h"
Quadtree::Quadtree()
{
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    level = QUAD_MIN_LEVEL;
}
Quadtree::Quadtree(int level, double x, double y, float width)
{
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    this->size = Rect(x, y);
    this->level = level;
    this->size = Rect(x, y, width);
}
Quadtree::Quadtree(LPCWSTR path)
{
    object = vector<LPGAMEOBJECT>();
    topLeftTree = NULL;
    topRightTree = NULL;
    botLeftTree = NULL;
    botRightTree = NULL;
    ifstream f;
    f.open(path);

    // current resource section flag
    int section = QUAD_SECTION_UNKNOWN;

    char str[MAX_QUAD_LINE];
    while (f.getline(str, MAX_QUAD_LINE))
    {
        string line(str);

        if (line[0] == '#') continue;	// skip comment lines	

        if (line == "[OBJECTS]") {
            section = QUAD_SECTION_OBJECTS; continue;
        }
        switch (section)
        {
        case QUAD_SECTION_OBJECTS: _ParseSection_OBJECTS_QT(line); break;
        }
    }

}
void Quadtree::_ParseSection_OBJECTS_QT(string line)
{
    vector<string> tokens = split(line);

    // skip invalid lines - an object set must have at least id, x, y
    if (tokens.size() < 2) return;

    int object_type = atoi(tokens[0].c_str());
    float x = (float)atof(tokens[1].c_str());
    float y = (float)atof(tokens[2].c_str());

    CGameObject* obj = NULL;

    switch (object_type)
    {
    case OBJECT_TYPE_BLACKWALKER: obj = new CBlackWalker(x, y); break;
    case OBJECT_TYPE_SOPHIA: obj = new CSophia(x, y); break;
    case OBJECT_TYPE_PLATFORM:
    {

        float cell_width = (float)atof(tokens[3].c_str());
        float cell_height = (float)atof(tokens[4].c_str());
        int length = atoi(tokens[5].c_str());
        int sprite_begin = atoi(tokens[6].c_str());
        int sprite_middle = atoi(tokens[7].c_str());
        int sprite_end = atoi(tokens[8].c_str());

        obj = new CPlatform(
            x, y,
            cell_width, cell_height, length,
            sprite_begin, sprite_middle, sprite_end
        );

        break;
    }
    break;


    default:
        DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
        return;
    }

    obj->SetPosition(x, y);;

    this->object.push_back(obj);

}

void Quadtree::AddObject(LPGAMEOBJECT obj)
{
    if (inBoundary(obj->x, obj->y))
        this->object.push_back(obj);
}
void Quadtree::Split()
{
    double pX = this->size.x;
    double pY = this->size.y;
    float width = this->size.width / 2;
    if (width <= MIN_WIDTH_OF_QUADTREE)
    {
        DebugOut(L"RRRRRR LEVEL %d SIZE %d %f %f\n", this->level, this->object.size(), this->size.x, this->size.y, width);
        return;
    }

    DebugOut(L"Quadtree::Split()  %f %f Quadtree::Split()\n", width, object.size());
    topLeftTree = new Quadtree(this->level + 1, pX, pY, width);
    topRightTree = new Quadtree(this->level + 1, pX + width, this->size.y, width);
    botLeftTree = new Quadtree(this->level + 1, pX, pY + width, width);
    botRightTree = new Quadtree(this->level + 1, pX + width, pY + width, width);
    for (int i = 0; i < object.size(); i++)
    {
        topLeftTree->AddObject(object[i]);
        topRightTree->AddObject(object[i]);
        botLeftTree->AddObject(object[i]);
        botRightTree->AddObject(object[i]);
    }
    topLeftTree->Split();
    topRightTree->Split();
    botLeftTree->Split();
    botRightTree->Split();
    DebugOut(L"LEVEL %d SIZE %d %f %f\n", this->level, this->object.size(), this->size.x, this->size.y);
    //DK dừng: width =1/2 camera     
}
bool Quadtree::inBoundary(double x, double y)
{
    return (x >= this->size.x &&
        x <= this->size.x + this->size.width &&
        y >= this->size.y &&
        y <= this->size.y + this->size.width);
}