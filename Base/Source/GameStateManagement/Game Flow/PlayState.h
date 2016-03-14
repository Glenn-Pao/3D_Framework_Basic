#pragma once

#include "timer.h"
#include "..\..\GameStateManagement\Master\GameState.h"
#include "..\..\Scenes\Master\ScenePlay2D.h"
#include "..\..\Scenes\Master\ScenePlay3D.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

#define TYPE_OF_VIEW 3	// 2 = 2D, 3 = 3D

class CPlayState : public CGameState
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

	static CPlayState* Instance() {
		return &thePlayState;
	}

protected:
	CPlayState() { }

private:
	static CPlayState thePlayState;
	int counter;

	//Declare variables to store the last and current mouse position
	double mouse_last_x, mouse_last_y, mouse_diff_x, mouse_diff_y;
	double camera_yaw, camera_pitch;

	GLFWwindow* m_window;

	// The handler for the scene
#if TYPE_OF_VIEW == 3
	CScenePlay3D *scene;	// Use this for 3D gameplay
#else
	CSceneAssignment2D *scene;	// Use this for 2D gameplay
#endif
};