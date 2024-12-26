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
#include "CheckPoint.h"
#include "Ladder.h"
#include "WaterSurface.h"


class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;

	// A play scene has to have a player, right?
	LPGAMEOBJECT activePlayer; // The currently active player (e.g., Sophia or Jason)

	LPGAMEOBJECT sophia; // Sophia object
	LPGAMEOBJECT jason;  // Jason object

	vector<LPGAMEOBJECT> objects;
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

	LPGAMEOBJECT GetActivePlayer() { return activePlayer; } // Get the currently active player
	void SetActivePlayer(LPGAMEOBJECT player) { activePlayer = player; } // Switch active player

	LPGAMEOBJECT GetSophia() { return sophia; } // Get Sophia
	void SetSophia(LPGAMEOBJECT obj) { sophia = obj; } // Set Sophia object

	LPGAMEOBJECT GetJason() { return jason; } // Get Jason
	void SetJason(LPGAMEOBJECT obj) { jason = obj; } // Set Jason object

	void AddObject(LPGAMEOBJECT obj) { this->objects.push_back(obj); } // add obj to scene
	void DeleteObject(LPGAMEOBJECT obj); // New function to delete an object

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;
