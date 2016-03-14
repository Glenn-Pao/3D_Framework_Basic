#include <iostream>
using namespace std;

#include "playstate.h"
#include "..\..\GameStateManagement\Master\GameState.h"
#include "..\..\GameStateManagement\Master\GameStateManager.h"
#include "..\Menu Flow\MenuState.h"
CPlayState CPlayState::thePlayState;

void CPlayState::Init()
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Init\n" << endl;
#endif
	counter = 0;

#if TYPE_OF_VIEW == 3
	scene = new CScenePlay3D();	// Use this for 3D gameplay
#else
	scene = new CSceneAssignment2D();	// Use this for 2D gameplay
#endif
	scene->Init(0);
}

void CPlayState::Init(const int width, const int height)
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Init\n" << endl;
#endif
	counter = 0;

#if TYPE_OF_VIEW == 3
	scene = new CScenePlay3D();	// Use this for 3D gameplay
#else
	scene = new CSceneAssignment2D();	// Use this for 2D gameplay
	//scene = new CSceneManager2D(width, height);	// Use this for 2D gameplay
#endif
	scene->Init(0);
}

void CPlayState::Cleanup()
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Cleanup\n" << endl;
#endif
	// Delete the scene
	scene->Exit();
	delete scene;
	scene = NULL;
}

void CPlayState::Pause()
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Pause\n" << endl;
#endif
}

void CPlayState::Resume()
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Resume\n" << endl;
#endif
}

void CPlayState::HandleEvents(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	
#endif
}

void CPlayState::HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status)
{
#if GSM_DEBUG_MODE
	
#endif
	if (status)
		scene->UpdatePlayerStatus(key);
}

void CPlayState::HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
	const int button_Left, const int button_Middle, const int button_Right)
{
#if GSM_DEBUG_MODE
	
#endif
}


void CPlayState::Update(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Update\n" << endl;
#endif
	// Update the scene
	scene->Update(0.16667);
}

void CPlayState::Update(CGameStateManager* theGSM, const double m_dElapsedTime)
{
	// Update the scene
	scene->Update(m_dElapsedTime);
}

void CPlayState::Draw(CGameStateManager* theGSM)
{
#if GSM_DEBUG_MODE
	cout << "CPlayState::Draw : " << counter << "\n" << endl;
#endif

	// Render the scene
	scene->Render();
}
