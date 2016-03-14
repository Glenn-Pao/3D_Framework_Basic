#ifndef SCENE_GAME_BASE_H
#define SCENE_GAME_BASE_H

#include "ScenePlay3D.h"
#include "..\..\Light.h"
#include "..\..\Minimap.h"
#include "Vector2.h"
#include "..\..\Player.h"

//#include "..\..\GameMechanics\SavingAndLoading\GameInfo.h"

/*
	This is the base class containing the common information required for each game scene. It is to be inherited later on from the individual games.

	Done by Almeda Glenn Paolo Maestro
*/
class CSceneGameBase : public Scene
{
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,

		


		// Alpha Black Quad
		GEO_ALPHA_BLACK_QUAD,
		// Dark Surrounding
		GEO_DARK_SURROUNDING,
		GEO_BLACK_QUAD,

		NUM_GEOMETRY,
	};
public:
	CSceneGameBase();
	CSceneGameBase(const int m_window_width, const int m_window_height);
	~CSceneGameBase();

	virtual void Init(int level) = 0;
	virtual void PreInit() = 0;
	virtual void Update(double dt) = 0;
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true) = 0;
	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key) = 0;
	virtual void UpdatePlayerStatus(const unsigned char key, const bool status = true) = 0;
	virtual void Render() = 0;
	virtual void Exit()= 0;

	// Find and Set the actual offset of hero
	void SetHeroOffset();

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_FIRE,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};
	void RenderWaypoints();

	CScenePlay3D sceneManager;

protected:
	Mesh* meshList[NUM_GEOMETRY];

	// Handle to the minimap
	CMinimap* m_cMinimap;

	// Hero's information
	CPlayer* theHero;
	void RenderHero();

	//CWaypoints *waypoints;

	// Enemies
	//vector<CEnemy*> theEnemies;

private:
	unsigned m_vertexArrayID;
	int m_window_width;
	int m_window_height;

};

#endif