#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

// The default camera speed
static const float CAMERA_SPEED = 500.f;

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up, std::vector<unsigned char> heightmap, Vector3 tScale)
{
	IsOpen = false;
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->heightmap = heightmap;
	this->tScale = tScale;

	// Initialise the camera movement flags
	for(int i=0; i<255; i++){
		myKeys[i] = false;
	}

	//Initialise the camera type
	sCameraType = LAND_CAM;
}
/********************************************************************************
Set Camera Type
********************************************************************************/
void Camera3::SetCameraType(CAM_TYPE sCameraType)
{
	this->sCameraType = sCameraType;
}
/********************************************************************************
Get Camera Type
********************************************************************************/
Camera3::CAM_TYPE Camera3::GetCameraType(void)
{
	return sCameraType;
}
void Camera3::Update(double dt)
{
	if ( myKeys['w'] == true)
	{
		MoveForward( dt );
		myKeys['w'] = false;
	}
	if (myKeys['s'] == true)
	{
		MoveBackward( dt );
		myKeys['s']	= false;
	}
	if (myKeys['a'] == true)
	{
		MoveLeft( dt );
		myKeys['a']	= false;
	}
	if (myKeys['d'] == true)
	{
		MoveRight( dt );
		myKeys['d']	= false;
	}

	//Update the camera direction based on mouse move
	// left-right rotate
	if ( Application::camera_yaw != 0 )
		Yaw( dt );
	if ( Application::camera_pitch != 0 )
		Pitch( dt );

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}
/******************************************************************************
**
Walk forward or backward. You can add in a deadzone here (situations where character cannot move or do certain actions)
*******************************************************************************
*/
void Camera3::Walk(const double dt)
{
	if (dt > 0)
		MoveForward(dt);
	else if (dt < 0)
		MoveBackward(abs(dt));
}
/******************************************************************************
**
Strafe left or right. You can add in a deadzone here.
*******************************************************************************
*/
void Camera3::Strafe(const double dt)
{
	if (dt > 0)
		MoveRight(dt);
	else if (dt < 0)
		MoveLeft(abs(dt));
}
/******************************************************************************
**
Pitch. You can add in a deadzone here.
*******************************************************************************
*/
void Camera3::Pitch(const double dt)
{
	if ( Application::camera_pitch > 0.1 )
		LookUp( dt );
	else if ( Application::camera_pitch < -0.1 )
		LookDown( dt );
}
/********************************************************************************
LookUp
********************************************************************************/
void Camera3::LookUp(const double dt)
{
	float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}
/********************************************************************************
LookDown
********************************************************************************/
void Camera3::LookDown(const double dt)
{
	float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}
/********************************************************************************
Yaw. You can add in a deadzone here.
********************************************************************************/
void Camera3::Yaw(const double dt)
{
	//turn right -> positive value
	if ( Application::camera_yaw > 0.1 )
		TurnRight( dt );
	//turn left -> negative value
	else if ( Application::camera_yaw < -0.1 )
		TurnLeft( dt );
}
/********************************************************************************
Turn Left. You can add in a deadzone here.
********************************************************************************/
void Camera3::TurnLeft(const double dt)
{
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}
/********************************************************************************
Turn Left. You can add in a deadzone here.
********************************************************************************/
void Camera3::TurnRight(const double dt)
{
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}
// Update Camera status
void Camera3::UpdateStatus(const unsigned char key)
{
	myKeys[key] = true;
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

/********************************************************************************
Move the camera forward
********************************************************************************/
void Camera3::MoveForward(const double dt)
{
	Vector3 view = (target - position).Normalized();
	if (sCameraType == LAND_CAM)
	{
		view.y = 0;
	}
	position += view * CAMERA_SPEED * (float)dt;
	target += view * CAMERA_SPEED * (float)dt;
	
}
/********************************************************************************
Move the camera backward
********************************************************************************/
void Camera3::MoveBackward(const double dt)
{
	Vector3 view = (target - position).Normalized();

	if (sCameraType == LAND_CAM)
	{
		view.y = 0;
	}

	position -= view * CAMERA_SPEED * (float)dt;
	target -= view * CAMERA_SPEED * (float)dt;
}
/********************************************************************************
Move the camera left
********************************************************************************/
void Camera3::MoveLeft(const double dt)
{
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position -= right * CAMERA_SPEED * (float)dt;
	target -= right * CAMERA_SPEED * (float)dt;
}
/********************************************************************************
Move the camera right
********************************************************************************/
void Camera3::MoveRight(const double dt)
{
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position += right * CAMERA_SPEED * (float)dt;
	target += right * CAMERA_SPEED * (float)dt;
}