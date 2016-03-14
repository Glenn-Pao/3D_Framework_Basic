#ifndef SCENE_ASSIGNMENT_2D_H
#define SCENE_ASSIGNMENT_2D_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Vector2.h"


class CSceneAssignment2D : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_LIGHTENABLED,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE1,			//2nd texture
		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_TEXT,
		GEO_TERRAIN,
		GEO_TEST,
		NUM_GEOMETRY,
	};

public:
	CSceneAssignment2D(void);
	~CSceneAssignment2D(void);
	CSceneAssignment2D(const int m_window_width, const int m_window_height);
	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderBackground();
	void Render2DMesh(Mesh *mesh, const bool enableLight, const int size = 1, const int x = 0, const int y = 0, const bool rotate = false, const bool flip = false);

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_FIRE,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};

private:
	//Terrain "don't even need this but have no idea why camera need it"
	std::vector<unsigned char>m_heightMap;
	Vector3 TERRAIN_SCALE;

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	float rotateAngle;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	int m_window_width;
	int m_window_height;

	float fps;

	//State changer
	unsigned short State;


};

#endif