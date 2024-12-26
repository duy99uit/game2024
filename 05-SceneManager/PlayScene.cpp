#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Background.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());
	int tag = 0;
	float newX = 0;
	float newY = 0;
	if (tokens.size() > 3) {
		DebugOut(L"[INFO] CBlackWalker <created>>>>>! %d\n", tag);
		tag = (int)atof(tokens[3].c_str());
	}
	if (tokens.size() > 4) {
		newX = (float)atof(tokens[3].c_str());
		newY = (float)atof(tokens[4].c_str());
		DebugOut(L"[INFO] CCheckPointCCheckPoint <created>>>>>! %d\n", tag);
	}
		

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_JASON:
		if (player!=NULL)
		{
			DebugOut(L"[ERROR] JASON object was created before!\n");
			return;
		}
		/*obj = new CJason(x,y); 
		player = (CJason*)obj;  */
		obj = new CSophia(x, y);
		sophia = (CSophia*)obj;
		player = sophia;
		SetActivePlayer(sophia);

		DebugOut(L"[INFO] Player object has been created! %d\n", x, y);
		break;
	/*case OBJECT_TYPE_BLACKWALKER: obj = new CBlackWalker(x,y); break;*/
	case OBJECT_TYPE_BLACKWALKER:
		obj = new CBlackWalker(x, y, tag);
		obj->SetTag(tag); 
		DebugOut(L"[INFO] CBlackWalker created! %d\n", tag);
		break;
	case OBJECT_TYPE_FLYINGBOMB: obj = new CFlyingBomb(x, y); break;
	case OBJECT_TYPE_BEETLEHEAD: obj = new CBeetleHead(x, y); break;
	case OBJECT_TYPE_POWER_P: obj = new CPower(x, y); break;
	case OBJECT_TYPE_BOUCINGBOMB: obj = new CBouncingBomb(x, y); break;
	case OBJECT_TYPE_PLATFORM_WALKER: obj = new CPlatformWalker(x, y); break;
	case OBJECT_TYPE_ROTATING_GUN: obj = new CRotatingGun(x, y); break;
	case OBJECT_TYPE_GUN_WALKER: obj = new CGunWalker(x, y); break;
	case OBJECT_TYPE_BEE_HEAD: obj = new CBeeHead(x, y); break;
	case OBJECT_TYPE_JELLY_FISH: obj = new CJellyFish(x, y); break;
	case OBJECT_TYPE_CHECKPOINT: obj = new CCheckPoint(x, y, newX, newY); break;
	case OBJECT_TYPE_LADDER: obj = new CLadder(x, y); break;
	case OBJECT_TYPE_WATERSURFACE: obj = new CWaterSurface(x, y); break;
	/*case OBJECT_TYPE_SOPHIA: obj = new CSophia(x, y); break;*/
	/*case OBJECT_TYPE_BRICK: obj = new CBrick(x,y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;*/




	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::_ParseSection_QUAD(string line)
{
	DebugOut(L"READ QUADTREE START, HAVE %d OBJECTS\n");
	vector<string> tokens = split(line);
	DebugOut(L"--> %s\n", ToWSTR(line).c_str());
	LPCWSTR path = ToLPCWSTR(tokens[0]);
	quadtree = new Quadtree(path);
	vector<LPGAMEOBJECT> quad = quadtree->getAllObjectInQT();
	objects.insert(objects.end(), quad.begin(), quad.end());
	DebugOut(L"READ QUADTREE SUCCESS, HAVE %d %d OBJECTS\n", objects.size(), quad);
	quadtree->Split();
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[QUADTREE]") {
			DebugOut(L"[INFO] vo day parse quad \n");
			section = SCENE_SECTION_QUAD; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_QUAD: _ParseSection_QUAD(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{

	vector<LPGAMEOBJECT> quad = quadtree->getAllObjectInQT();
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	objects.insert(objects.end(), quad.begin(), quad.end());
	coObjects.insert(coObjects.end(), quad.begin(), quad.end());
	// skip the rest if scene was already unloaded (Jason::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow jason
	float player_x, player_y;
	player->GetPosition(player_x, player_y);

	CGame *game = CGame::GetInstance();
	Camera* camera = CGame::getCamera();
	camera->SetSize(game->GetScreenWidth(), game->GetScreenHeight());
	camera->Update(player_x, player_y);

	//CGame* game = CGame::GetInstance();
	//cx -= game->GetBackBufferWidth() / 2;
	//cy -= game->GetBackBufferHeight() / 2;

	//if (cx < 0) cx = 0;

//	CGame::GetInstance()->SetCamPos(cx,cy);
	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}