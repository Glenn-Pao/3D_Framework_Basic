#pragma once

#include "Vector3.h"
#include <stdio.h>

class CProjectile
{
public:
	CProjectile(void);
	~CProjectile(void);

	enum PROJECTILE_TYPE
	{
		PROJ_TYPE_DISCRETE,
		PROJ_TYPE_RAY,
		NUM_PROJ_TYPE
	};
private:
	// Boolean flag to indicate if this projectile is active. If not active, then do not compute/update
	bool m_bActive;
public:
	// Update the status of this projectile
	void Update(const double dt);
	// Activate the projectile. true == active, false == inactive
	void SetActivate(bool m_bActivate);
	// get status of the projectile. true == active, false == inactive
	bool GetStatus(void);
	// Get the position of the projectile
	Vector3 GetPosition();
	// Get the direction of the projectile
	Vector3 GetDirection(void);
	// Get Hit Points
	int GetHitPoints(void);
	// Get the length of the ray projectile
	float GetLength();
	// Get the projectile type
	int GetType(void);
	// Get Distance travelled by the projectile
	float GetDistanceTravelled(void);

	// Set the position of the projectile
	void SetPosition(Vector3 theNewPosition);
	// Set the direction of the projectile
	void SetDirection(Vector3 theNewDirection);
	// Set speed
	void SetSpeed(const float speed);
	// Set Hit Points
	void SetHitPoints(const int hitPoints);
	// Set the length of the ray projectile
	void SetLength(const float theLength);
	// Set the projectile type
	void SetType(const int theType);
	// Set Distance travelled by the projectile
	void SetDistanceTravelled(const float distanceTravelled);
private:
	// The position of the projectile
	Vector3 thePosition;
	// The direction of the projectile
	Vector3 theDirection;
	// Speed
	float speed;
	// Hit Points
	int hitPoints;
	// The length of the ray projectile
	float theLength;
	// flag to indicate if this is a sweep projectile. 0 = discrete, 1 = sweep
	int theType;
	// Distance travelled by the projectile
	float distanceTravelled;
};
