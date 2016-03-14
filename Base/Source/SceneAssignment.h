#ifndef SCENE_ASSIGNMENT_H
#define SCENE_ASSIGNMENT_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Particle.h"
#include "Fog.h"
#include "Physics.h"
#include "Player.h"
#include "DepthFBO.h"
#include <vector>

class SceneAssignment : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE1,			//2nd texture
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_FOG_COLOR,
		U_FOG_START,
		U_FOG_END,
		U_FOG_DENSITY,
		U_FOG_TYPE,
		U_FOG_ENABLED,
		U_LIGHT_DEPTH_MVP_GPASS,
		U_LIGHT_DEPTH_MVP,
		U_SHADOW_MAP,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE		//for the environment
	{
		GEO_AXES,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_QUAD,
		GEO_CUBE,
		GEO_RING,
		GEO_CONE,
		GEO_LEFT,
		GEO_OBJECT,
		GEO_TEXT,
		GEO_SKYPLANE,
		GEO_TERRAIN,
		GEO_FOG,
		GEO_SNOW,
		NUM_GEOMETRY,
	};
	enum RENDER_PASS
	{
		RENDER_PASS_PRE,
		RENDER_PASS_MAIN,
	};
public:
	SceneAssignment(void);
	SceneAssignment(const int m_window_width, const int m_window_height);
	~SceneAssignment(void);

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void ParametersInit();		//definitions of OpenGL parameters goes here
	void ObjectsInit();			//other objects
	void TerrainInit();			//terrain-related items

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size=1.0f, float x=0.0f, float y=0.0f);
	void RenderMesh(Mesh *mesh, bool enableLight, bool enableFog = false);
	void RenderTerrain();
	void RenderGUI();

	//update the player's coordinates
	virtual void UpdatePlayerStatus(const unsigned char key);	
	virtual void UpdateCameraStatus(const unsigned char key);


	//new items
	//particles
	int m_objectcount;
	Vector3 m_gravity;
	std::vector<Particle *> m_parList;

	Particle* FetchParticle();
	void UpdateParticle(double dt);
	void ToggleFog();
	void RenderParticle(Particle *particle);
	
	//billboard stuff
	void RenderSprites();			//lico and michele comes here
	Vector3 posTree;
	double move;					//move code for lico

	const float GetHeightMapY(float x, float z);
	void setPlayerHeight(Camera3& camera, std::vector<unsigned char> &heightMap, const Vector3& terrainSize, bool IgnoreHM);

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];

	float rotateAngle;
	
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	void RenderSkyPlane(Mesh* mesh, Color color, int slices, float PlanetRadius,
float height, float hTile, float vTile);

	//Terrain
	std::vector<unsigned char>m_heightMap;
	Vector3 TERRAIN_SCALE;

	Camera3 camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[2];
	Fog fog[2];

	bool bLightEnabled;

	float fps;
	bool bFog;

	//Handle to the player class
	CPlayer* thePlayer;

	//Physics
	CPhysics thePhysics;

	//Light Depth Buffer
	unsigned m_gPassShaderID;
	DepthFBO m_lightDepthFBO;
	Mtx44 m_lightDepthProj;
	Mtx44 m_lightDepthView;
	RENDER_PASS m_renderPass;
};

#endif