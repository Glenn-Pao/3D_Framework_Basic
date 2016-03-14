#include <iostream>
using namespace std;

#include "GameStateManager.h"
#include "gamestate.h"
#include "menustate.h"
#include "introstate.h"
#include "playstate.h"

CIntroState CIntroState::theIntroState;

void CIntroState::Init()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Init\n" << endl;
#endif
#if TYPE_OF_VIEW == 3
	intro_scene = new SceneAssignment();	// Use this for 3D gameplay
#else
	intro_scene = new CSceneAssignment2D();	// Use this for 2D gameplay
#endif
	
	intro_scene->Init();
}

void CIntroState::Init(const int width, const int height)
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Init\n" << endl;
#endif
#if TYPE_OF_VIEW == 3
	intro_scene = new SceneAssignment();	// Use this for 3D gameplay
#else
	intro_scene = new CSceneAssignment2D();	// Use this for 2D gameplay
#endif
	intro_scene->Init();
}

void CIntroState::Cleanup()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Cleanup\n" << endl;
#endif
	// Delete the scene
	intro_scene->Exit();
	delete intro_scene;
	intro_scene = NULL;
}

void CIntroState::Pause()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Pause\n" << endl;
#endif
}

void CIntroState::Resume()
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Resume\n" << endl;
#endif
}

void CIntroState::HandleEvents(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
#endif
}

void CIntroState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
#if GSM_DEBUG_MODE
#endif
	if (status)
		intro_scene->UpdateCameraStatus(key);
	//if (key == 32)
		//theGSM->ChangeState(CMenuState::Instance());
}

void CIntroState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
							   const int button_Left, const int button_Middle, const int button_Right)
{
#if GSM_DEBUG_MODE
#endif
}

void CIntroState::Update(CGameStateManager* theGSM) 
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Update\n" << endl;
#endif
}

void CIntroState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
}

void CIntroState::Draw(CGameStateManager* theGSM) 
{
#if GSM_DEBUG_MODE
	cout << "CIntroState::Draw\n" << endl;
#endif
	intro_scene->Render();
}
