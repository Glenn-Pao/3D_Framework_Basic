#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Player.h"
#include "Camera3.h"
#include "LoadHmap.h"
#include "Light.h"
#include "Particle.h"
#include <iostream>
#include <sstream>

using namespace std;

class CPhysics
{
	const static int CAMERA_REPELL = 10;
public:
	CPhysics(void);
	~CPhysics(void);

	// Get the gravity
	Vector3 getGravity(void); 
	// Set the gravity
	void setGravity(Vector3); 

	// Check height of terrain
	const float GetHeightMapY(float x, float z, std::vector<unsigned char> &heightMap,const Vector3& terrainSize);

	// Set player height from terrain
	void setPlayerHeight(Camera3&,CPlayer*&, std::vector<unsigned char> &heightMap,const Vector3& terrainSize, bool m_bIgnoreHM = false );

	//************** Functions that we might need next time ************************//

	// Check collision, commented out for future references
	//bool checkCollisionBetweenOBJ(CPlayer*, CObj*);
	//void collisionResponseBetweenOBJ(Camera3&,CPlayer*&, CObj*&, double);

	//************** Functions that we might need next time ************************//

private:
	Vector3 m_Gravity;
	float m_fOffset;
	float m_In_World_Time;
	float m_time_interval;
	Vector3 diff;
};