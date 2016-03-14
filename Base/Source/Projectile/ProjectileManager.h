#pragma once

#include "Projectile.h"

class CProjectileManager
{
public:
	CProjectileManager(void);
	~CProjectileManager(void);

	// Projectile
	bool AddProjectile(Vector3 position, Vector3 direction, const float speed = 10.0f, const int hitPoints = 1);
	bool AddRayProjectile(Vector3 position, Vector3 direction, const float speed = 10.0f, const float length = 10.0f, const int hitPoints = 1);
	void SetProjectile(const int index, Vector3 position, Vector3 direction);
	void RemoveProjectile(const int index);

	// Access modifiers
	int GetMaxNumberOfProjectiles(void);
	int GetNumberOfActiveProjectiles(void);
	CProjectile* GetProjectile(const int index);

	// Check methods
	bool IsValid(const int index);
	bool IsActive(const int index);

	// Update
	void Update(const double dt);

	// Variables
	CProjectile** theListOfProjectiles;
	int NumOfActiveProjectile;
	int CurrentEmptyProjectile;
	Vector3 Boundary_TopLeft, Boundary_BottomRight;
};

