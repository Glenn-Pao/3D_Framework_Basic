
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
double Application::mouse_last_x = 0.0, Application::mouse_last_y = 0.0, 
	   Application::mouse_current_x = 0.0, Application::mouse_current_y = 0.0,
	   Application::mouse_diff_x = 0.0, Application::mouse_diff_y = 0.0;
double Application::camera_yaw = 0.0, Application::camera_pitch = 0.0, Application::camera_roll = 0.0;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

bool Application::GetMouseUpdate()
{
    glfwGetCursorPos(m_window, &mouse_current_x, &mouse_current_y);

	// Calculate the difference in positions
	mouse_diff_x = mouse_current_x - mouse_last_x;
	mouse_diff_y = mouse_current_y - mouse_last_y;

	//Calculate the yaw and pitch
	camera_yaw = (float) mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
	camera_pitch = mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );

	// Do a wraparound if the mouse cursor has gone out of the deadzone
	if ((mouse_current_x < m_window_deadzone) || (mouse_current_x > m_window_width-m_window_deadzone))
	{
		mouse_current_x = m_window_width >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}
	if ((mouse_current_y < m_window_deadzone) || (mouse_current_y > m_window_height-m_window_deadzone))
	{
		mouse_current_y = m_window_height >> 1;
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}

	// Store the current position as the last position
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;

	Button_Left = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
	Button_Middle = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE);
	Button_Right = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT);

	theGSM->HandleEvents(mouse_current_x, mouse_current_y, Button_Left, Button_Middle, Button_Right);

	// Get the mouse button status
	if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		//scene->UpdateWeaponStatus(scene->WA_FIRE);

    return false;
}

bool Application::GetKeyboardUpdate()
{
	
	if (IsKeyPressed('A'))
	{
		theGSM->HandleEvents('a');
	}
	else
	{
		theGSM->HandleEvents('a', false);
	}
	if (IsKeyPressed('D'))
	{
		theGSM->HandleEvents('d');
	}
	else
	{
		theGSM->HandleEvents('d', false);
	}
	if (IsKeyPressed('W'))
	{
		theGSM->HandleEvents('w');
	}
	else
	{
		theGSM->HandleEvents('w', false);
	}
	if (IsKeyPressed('S'))
	{
		theGSM->HandleEvents('s');
	}
	else
	{
		theGSM->HandleEvents('s', false);
	}
	if (IsKeyPressed('R'))
	{
		theGSM->HandleEvents('r');
	}
	else
	{
		theGSM->HandleEvents('r', false);
	}
	if (IsKeyPressed('Q'))
	{
		theGSM->HandleEvents('q');
	}
	else
	{
		theGSM->HandleEvents('q', false);
	}
	if (IsKeyPressed('E'))
	{
		theGSM->HandleEvents('e');
	}
	else
	{
		theGSM->HandleEvents('e', false);
	}
	// Jump
	if (IsKeyPressed(32))
	{
		theGSM->HandleEvents(32);
	}
	// Pause
	if (IsKeyPressed(VK_ESCAPE))
	{
		theGSM->HandleEvents(VK_ESCAPE);
	}
	// Rotate camera
	if (IsKeyPressed(VK_LEFT))
	{
		theGSM->HandleEvents(VK_LEFT);
	}
	else
	{
		theGSM->HandleEvents(VK_LEFT, false);
	}
	if (IsKeyPressed(VK_RIGHT))
	{
		theGSM->HandleEvents(VK_RIGHT);
	}
	else
	{
		theGSM->HandleEvents(VK_RIGHT, false);
	}
	if (IsKeyPressed(VK_UP))
	{
		theGSM->HandleEvents(VK_UP);
	}
	else
	{
		theGSM->HandleEvents(VK_UP, false);
	}
	if (IsKeyPressed(VK_DOWN))
	{
		theGSM->HandleEvents(VK_DOWN);
	}
	else
	{
		theGSM->HandleEvents(VK_DOWN, false);
	}
	return true;
}

Application::Application()
: scene(NULL), theGSM(NULL)
{
}

Application::~Application()
{
	if (theGSM)
	{
		delete theGSM;
		theGSM = NULL;
	}
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(m_window_width, m_window_height, "DM2231_Framework", NULL, NULL);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	// Hide the cursor
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Set these 2 variables to zero
	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_ThreadOne = 0.0;
	m_dAccumulatedTime_ThreadTwo = 0.0;

	// Initialise the GSM
	theGSM = new CGameStateManager();
	theGSM->Init("DM224 with Game State Management", 800, 600);
	theGSM->ChangeState(CPlayState::Instance());
}

void Application::Run()
{
	//Main Loop
#if TYPE_OF_VIEW == 3
	scene = new CScenePlay3D();
	//scene = new SceneAssignment(m_window_width, m_window_height);	// Use this for 3D gameplay
#else
	scene = new SceneAssignment();
	//scene = new SceneAssignment(m_window_width, m_window_height);	// Use this for 2D gameplay
#endif
	scene->Init(0);

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		// Get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;
		if (m_dAccumulatedTime_ThreadOne > 0.03)
		{
			GetMouseUpdate();
			GetKeyboardUpdate();
			//scene->Update(m_dElapsedTime);
			//theGSM->HandleEvents();
			theGSM->Update(m_dElapsedTime);
			m_dAccumulatedTime_ThreadOne = 0.0;
		}
		if (m_dAccumulatedTime_ThreadTwo > 1.0)
		{
			//UpdateAI();
			m_dAccumulatedTime_ThreadTwo = 0.0;
		}
		// Render the scene
		theGSM->Draw();
	//	scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	theGSM->Cleanup();
	//scene->Exit();
	delete scene;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
