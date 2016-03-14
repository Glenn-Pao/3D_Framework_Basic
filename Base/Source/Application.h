#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "SceneAssignment.h"
#include "GameStateManager.h"
#include "IntroState.h"
#include "PlayState.h"

// 2 = 2D, 3 = 3D Level
// If you want more levels
// you need to change the TOV
// Example: (2 = 2D, 3 = 3D Level1, 4 = 3D Level2)
#define TYPE_OF_VIEW 3	

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	bool GetMouseUpdate();
	bool GetKeyboardUpdate();
	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch, camera_roll;

private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 100;
	const static int m_window_width = 800;
	const static int m_window_height = 600;
	// Declare the buttons
	int Button_Left;
	int Button_Middle;
	int	Button_Right;
	//Declare a window object
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

	// The handler for the scene
#if TYPE_OF_VIEW == 3
	SceneAssignment *scene;	// Use this for 3D gameplay
#else
	SceneAssignment *scene;	// Use this for 2D gameplay
#endif
	CGameStateManager* theGSM;
};

#endif