#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Jason.h"
#include "BlackWalker.h"
#include "Sophia.h"
#include "SophiaBullet.h"
#include "Power.h"
#include "BouncingBomb.h"
#include "PlatformWalker.h"
#include "FlyingBomb.h"
#include "BeetleHead.h"
#include "Quadtree.h"
#include "Define.h"
#include "RotatingGun.h"
#include "GunWalker.h"
#include "BeeHead.h"
#include "JellyFish.h"
#include "RotatingBullet.h"


class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> tree_objects;
	Quadtree* quadtree;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_QUAD(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	void AddObject(LPGAMEOBJECT obj) { this->objects.push_back(obj); } // add obj to scene

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;
