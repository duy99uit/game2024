#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Jason.h"
#include "Sophia.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	/*CJason* jason = (CJason *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	jason->HandleKeyDown(KeyCode);*/
	CSophia* sophia = (CSophia*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	sophia->HandleKeyDown(KeyCode);
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	/*CJason* jason = (CJason*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	jason->HandleKeyUp(KeyCode);*/
	CSophia* sophia = (CSophia*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	sophia->HandleKeyUp(KeyCode);
	

}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CJason* jason = (CJason*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	/*jason->HandleKeyState();*/
}