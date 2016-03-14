#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include <vector>

class Camera3 : public Camera
{
public:
	enum CAM_TYPE
	{
		LAND_CAM,
		AIR_CAM,
		NUM_CAM_TYPE
	};
	virtual void SetCameraType(CAM_TYPE sCameraType);
	virtual CAM_TYPE GetCameraType(void);
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 tScale;
	std::vector<unsigned char> heightmap;

	bool IsOpen;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up, std::vector<unsigned char> heightmap, Vector3 tScale);
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateStatus(const unsigned char key, const bool status = true);
	virtual void Reset();

	virtual void MoveForward(const double dt);
	virtual void MoveBackward(const double dt);
	virtual void MoveLeft(const double dt);
	virtual void MoveRight(const double dt);

	// Basic methods
	virtual void TurnLeft(const double dt);
	virtual void TurnRight(const double dt);
	virtual void LookUp(const double dt);
	virtual void LookDown(const double dt);

	// Applied methods
	virtual void Pitch(const double dt);
	virtual void Yaw(const double dt);
	virtual void Walk(const double dt);
	virtual void Strafe(const double dt);
private:
	bool myKeys[255];
	CAM_TYPE sCameraType;
};

#endif