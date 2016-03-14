#include "Occlusion.h"
#include <iostream>

using namespace std;

/********************************************************************************
 Constructor
 ********************************************************************************/
COcclusion::COcclusion(void)
	: screenCoordinate( 0.0f, 0.0f, 30.0f )	//	Camera's default position in CSceneManager
	, screenNormal( 0.0f, 0.0f, -1.0f )		//	Camera's default direction in CSceneManager
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
COcclusion::~COcclusion(void)
{
}

/********************************************************************************
 Get the coordinate of the middle of the screen
 ********************************************************************************/
Vector3 COcclusion::GetScreenCoordinate(void)
{
	return screenCoordinate;
}

/********************************************************************************
 Get the normal of the screen
 ********************************************************************************/
Vector3 COcclusion::GetScreenNormal(void)
{
	return screenNormal;
}

/********************************************************************************
 Set the coordinate of the middle of the screen
 ********************************************************************************/
void COcclusion::SetScreenCoordinate(Vector3 screenCoordinate)
{
	this->screenCoordinate = screenCoordinate;
}

/********************************************************************************
 Set the normal of the screen
 ********************************************************************************/
void COcclusion::SetScreenNormal(Vector3 screenNormal)
{
	this->screenNormal = screenNormal;
	screenCoordinate = screenCoordinate + screenNormal * 0.5f;
}

/********************************************************************************
 Project an original coordinate onto the screen and return this value
 ********************************************************************************/
Vector3 COcclusion::GetProjectedCoordinate(Vector3 originalCoordinate)
{
	// Make a vector from the original coordinate to the screen
	Vector3 vec_orig_to_screen = originalCoordinate - screenCoordinate;

	// Calculate the perpendicular distance from the point to the screen
	float distance_orig_to_screen = vec_orig_to_screen.Dot( screenNormal );

	Vector3 projectedCoordinated = originalCoordinate - (distance_orig_to_screen * screenNormal);

	return projectedCoordinated;
}



/********************************************************************************
 PrintSelf
 ********************************************************************************/
void COcclusion::PrintSelf(void)
{
	cout << "COcclusion::PrintSelf(void)" << endl;
	cout << "===========================" << endl;
	cout << "screenCoordinate\t=\t[" << screenCoordinate.x << ", " << screenCoordinate.y << ", "<< screenCoordinate.z << "]" << endl;
	cout << "screenNormal\t\t=\t[" << screenNormal.x << ", " << screenNormal.y << ", "<< screenNormal.z << "]" << endl;

	Vector3 positionTest(10.0f, 0.0f, 0.0f);
	Vector3 projectedPosition = GetProjectedCoordinate( positionTest );

	cout << "positionTest\t\t=\t[" << positionTest.x << ", " << positionTest.y << ", "<< positionTest.z << "]" << endl;
	cout << "projectedPosition\t=\t[" << projectedPosition.x << ", " << projectedPosition.y << ", "<< projectedPosition.z << "]" << endl;
}