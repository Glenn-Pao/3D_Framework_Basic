#pragma once

#include "Vector3.h"

class COcclusion
{
public:
	// Constructor
	COcclusion(void);
	// Destructor
	~COcclusion(void);

	// Get the coordinate of the middle of the screen
	Vector3 GetScreenCoordinate(void);
	// Get the normal of the screen
	Vector3 GetScreenNormal(void);
	// Set the coordinate of the middle of the screen
	void SetScreenCoordinate(Vector3 screenCoordinate);
	// Set the normal of the screen
	void SetScreenNormal(Vector3 screenNormal);

	// Project an original coordinate onto the screen and return this value
	Vector3 GetProjectedCoordinate(Vector3 originalCoordinate);

	// PrintSelf
	void PrintSelf(void);

private:
	// The coordinate of the middle of the screen
	Vector3 screenCoordinate;
	// The normal of the screen
	Vector3 screenNormal;
};

