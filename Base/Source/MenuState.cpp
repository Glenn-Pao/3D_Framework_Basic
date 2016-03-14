#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "introstate.h"
#include "playstate.h"
#include "gamestate.h"
#include "menustate.h"
#include "Application.h"

CMenuState CMenuState::theMenuState;

void CMenuState::Init()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Init\n" << endl;
#endif
#if TYPE_OF_VIEW == 3
	menu_scene = new SceneAssignment();	// Use this for 3D gameplay
#else
	menu_scene = new CSceneAssignment2D();	// Use this for 2D gameplay
#endif
	menu_scene->Init();
	currStateMenu = STATE_PLAY;
}

void CMenuState::Init(const int width, const int height)
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Init\n" << endl;
#endif
#if TYPE_OF_VIEW == 3
	menu_scene = new SceneAssignment();	// Use this for 3D gameplay
#else
	menu_scene = new CSceneAssignment2D();	// Use this for 2D gameplay
#endif
	menu_scene->Init();
	currStateMenu = STATE_PLAY;
}

void CMenuState::Cleanup()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Cleanup\n" << endl;
#endif
	// Delete the scene
	menu_scene->Exit();
	delete menu_scene;
	menu_scene = NULL;
}

void CMenuState::Pause()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Pause\n" << endl;
#endif
	menu_scene->Exit();
	delete menu_scene;
}

void CMenuState::Resume()
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Resume\n" << endl;
#endif
}

void CMenuState::HandleEvents(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
#endif
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
#if GSM_DEBUG_MODE

#endif
	if (status)
		menu_scene->UpdateCameraStatus(key);
}

void CMenuState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{
#if GSM_DEBUG_MODE
#endif
}

void CMenuState::Update(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Update\n" << endl;
#endif
}

void CMenuState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
}

void CMenuState::Draw(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CMenuState::Draw\n" << endl;
#endif
	menu_scene->Render();
}
