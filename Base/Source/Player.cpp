#include "Player.h"

static float offsetY = 0.f;

//construct the default constructor with empty default parameters
CPlayer::CPlayer(void)
	: active(false)
	, pos(0, 0, 0)
	, scale(0, 0, 0)
{
}
//cannot do the same construction as the default because this will have different set of values
CPlayer::CPlayer(bool active, Vector3 pos, Vector3 scale)
{
	this->active = active;
	this->pos = pos;
	this->scale = scale;
}
//the destructor. nothing to destroy right now
CPlayer::~CPlayer(void)
{
}

void CPlayer::Init(bool active, Vector3 pos, Vector3 scale)
{
	this->active = active;
	this->pos = pos;
	this->scale = scale;
}

//set current status of player
void CPlayer::SetActive(bool active)
{
	this->active = active;
}
//get current status of player
bool CPlayer::GetActive(void)
{
	return active;
}
//set current position of player
void CPlayer::SetPosition(Vector3 pos)
{
	this->pos = pos;
}
//get current position of player
Vector3 CPlayer::GetPosition(void)
{
	return pos;
}
//set current scale/hitbox of player
void CPlayer::SetScale(Vector3 scale)
{
	this->scale = scale;
}
//get current scale/hitbox of player
Vector3 CPlayer::GetScale(void)
{
	return scale;
}

//set the position of player
void CPlayer::SetPositionX(float x)
{
	this->pos.x = x;
}
void CPlayer::SetPositionY(float y)
{
	this->pos.y = y;
}
void CPlayer::SetPositionZ(float z)
{
	this->pos.z = z;
}

//get the position of player
float CPlayer::GetPositionX(void)
{
	return pos.x;
}
float CPlayer::GetPositionY(void)
{
	return pos.y;
}
float CPlayer::GetPositionZ(void)
{
	return pos.z;
}

//set the Scale of player
void CPlayer::SetScaleX(float x)
{
	this->scale.x = x;
}
void CPlayer::SetScaleY(float y)
{
	this->scale.y = y;
}
void CPlayer::SetScaleZ(float z)
{
	this->scale.z = z;
}

//get the Scale of player
float CPlayer::GetScaleX(void)
{
	return scale.x;
}
float CPlayer::GetScaleY(void)
{
	return scale.y;
}
float CPlayer::GetScaleZ(void)
{
	return scale.z;
}
/*============= inventory-related codes for player ends here =================*/

void CPlayer::UpdateCameraStatus( const unsigned char& key, Camera3& camera)
{
	camera.UpdateStatus(key);
}
void CPlayer::UpdatePosition(double& dt, Camera3& camera)
{
	pos.Set(camera.position.x, camera.position.y-offsetY, camera.position.z);
}