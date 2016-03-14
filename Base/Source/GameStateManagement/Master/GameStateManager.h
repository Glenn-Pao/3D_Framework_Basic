#pragma once

#include <vector>
using namespace std;

class CGameState;

class CGameStateManager
{
public:

	void Init(const char* title, int width = 640, int height = 480,
		int bpp = 0, bool fullscreen = false);
	void Cleanup();

	void ChangeState(CGameState* state);
	void PushState(CGameState* state);
	void PopState();

	void HandleEvents();
	void HandleEvents(const unsigned char key, const bool status = true);
	void HandleEvents(const double mouse_x, const double mouse_y,
		const int button_Left, const int button_Middle, const int button_Right);
	void Update(const double m_dElapsedTime);
	void Draw();

	bool Running() { return m_bRunning; }
	void Quit() { m_bRunning = false; }

private:
	// the stack of states
	vector<CGameState*> StackOfStates;

	int m_window_width;
	int m_window_height;

	bool m_bRunning;
	bool m_bFullscreen;
};
