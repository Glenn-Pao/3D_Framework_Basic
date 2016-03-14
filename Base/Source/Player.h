#ifndef PLAYER_H
#define PLAYER_H

#include "Vector3.h"
#include "Camera3.h"
class CPlayer
{
public:
	CPlayer(void);
	CPlayer(bool active, Vector3 pos, Vector3 scale);
	~CPlayer(void);

	void Init(bool active, Vector3 pos, Vector3 scale);

	void SetActive(bool);
	bool GetActive(void);

	//a blanket definition of player's position
	void SetPosition(Vector3);
	Vector3 GetPosition(void);

	//a blanket definition of player's scale/hitbox
	void SetScale(Vector3 scale);
	Vector3 GetScale(void);

	//set the position of player
	void SetPositionX(float);
	void SetPositionY(float);
	void SetPositionZ(float);

	//get the position of player
	float GetPositionX(void);
	float GetPositionY(void);
	float GetPositionZ(void);

	//set the Scale of player
	void SetScaleX(float);
	void SetScaleY(float);
	void SetScaleZ(float);

	//get the Scale of player
	float GetScaleX(void);
	float GetScaleY(void);
	float GetScaleZ(void);

	virtual void UpdateCameraStatus( const unsigned char& key, Camera3& camera);
	virtual void UpdatePosition(double&, Camera3&);

private:
	Vector3 pos;	// position of player
	Vector3 scale;	// scale of hitbox of player
	bool active;	// if player is dead, this flips to false
	Camera3 camera;

};
#endif