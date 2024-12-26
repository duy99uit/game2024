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
	/*CSophia* sophia = (CSophia*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	sophia->HandleKeyDown(KeyCode);*/
	// Get the current play scene and active player
	LPPLAYSCENE playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	LPGAMEOBJECT activePlayer = playScene->GetActivePlayer();

	if (activePlayer != nullptr)
	{
		// Cast to appropriate player type and handle key press
		if (dynamic_cast<CSophia*>(activePlayer))
		{
			((CSophia*)activePlayer)->HandleKeyDown(KeyCode);
		}
		else if (dynamic_cast<CJason*>(activePlayer))
		{
			((CJason*)activePlayer)->HandleKeyDown(KeyCode);
		}
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	/*CJason* jason = (CJason*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	jason->HandleKeyUp(KeyCode);*/
	/*CSophia* sophia = (CSophia*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	sophia->HandleKeyUp(KeyCode);*/

	/*CPlayScene* currentScene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CGameObject* activePlayer = currentScene->GetActivePlayer();
	if (dynamic_cast<CSophia*>(activePlayer)) {
		((CSophia*)activePlayer)->HandleKeyUp(KeyCode);
	}
	else if (dynamic_cast<CJason*>(activePlayer)) {
		((CJason*)activePlayer)->HandleKeyUp(KeyCode);
	}*/

	// Get the current play scene and active player
	LPPLAYSCENE playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	LPGAMEOBJECT activePlayer = playScene->GetActivePlayer();

	if (activePlayer != nullptr)
	{
		// Cast to appropriate player type and handle key release
		if (dynamic_cast<CSophia*>(activePlayer))
		{
			((CSophia*)activePlayer)->HandleKeyUp(KeyCode);
		}
		else if (dynamic_cast<CJason*>(activePlayer))
		{
			((CJason*)activePlayer)->HandleKeyUp(KeyCode);
		}
	}
	

}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CJason* jason = (CJason*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	/*jason->HandleKeyState();*/
}