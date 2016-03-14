#include "SceneGameBase.h"

extern "C" {
#include "..\..\Lua\lua.h"
#include "..\..\Lua\lualib.h"
#include "..\..\Lua\lauxlib.h"
}

CSceneGameBase::CSceneGameBase()
	: m_cMinimap(NULL)
	, theHero(NULL)
{
}
CSceneGameBase::CSceneGameBase(const int m_window_width, const int m_window_height)
	: m_cMinimap(NULL)
	, theHero(NULL)
{
	sceneManager.m_window_width = m_window_width;
	sceneManager.m_window_height = m_window_height;
}

CSceneGameBase::~CSceneGameBase()
{
	/*for (int i = 0; i < (int)theEnemies.size(); i++)
	{
		if (theEnemies[i])
		{
			delete theEnemies[i];
			theEnemies[i] = NULL;
		}
	}*/
	if (m_cMinimap)
	{
		delete m_cMinimap;
		m_cMinimap = NULL;
	}
}