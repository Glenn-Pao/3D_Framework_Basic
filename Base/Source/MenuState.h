#pragma once

#include "gamestate.h"
#include "SceneAssignment.h"

#define TYPE_OF_VIEW 3	// 2 = 2D, 3 = 3D

class CMenuState : public CGameState
{
public:
	void Init();
	void Init(const int width, const int height);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* theGSM);
	void HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status = true);
	void HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y,
		const int button_Left, const int button_Middle, const int button_Right);
	void Update(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM, const double m_dElapsedTime);
	void Draw(CGameStateManager* theGSM);

	enum MENU_STATE
	{
		STATE_PLAY = 0,
		STATE_HELP,
		STATE_SCORE,
		STATE_OPTION,
		STATE_EXIT,
		MAX_STATES,
	};

	static CMenuState* Instance() {
		return &theMenuState;
	}

protected:
	CMenuState() { }

private:
	static CMenuState theMenuState;
	// The handler for the scene
#if TYPE_OF_VIEW == 3
	SceneAssignment *menu_scene;	// Use this for 3D gameplay
#else
	CSceneAssignment2D *menu_scene;	// Use this for 2D gameplay
#endif
	CMenuState::MENU_STATE currStateMenu;
};
