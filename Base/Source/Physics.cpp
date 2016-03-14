#include "Physics.h"

CPhysics::CPhysics(void)
{
	m_Gravity = Vector3(0,-9.8f,0);
	m_fOffset = 100;
	m_time_interval= 0;
}

CPhysics::~CPhysics(void)
{
}

// Get the gravity
Vector3 CPhysics::getGravity(void)
{
	return m_Gravity;
}
// Set the gravity
void CPhysics::setGravity(Vector3 gravity)
{
	this->m_Gravity = gravity;
}
//bool CPhysics::checkCollisionBetweenOBJ(CPlayer* go1, CObj* go2)
//{
//	Vector3 obj1 = go1->GetPosition();
//	Vector3 obj2 = go2->getPosition();
//	Vector3 halfScale = (go2->getScale() + go2->getOffset()) * 0.5;
//
//	//AABB to AABB collision detection
//	if( obj1.x + go1->GetScale().x > obj2.x - halfScale.x  &&
//		obj1.x - go1->GetScale().x < obj2.x + halfScale.x  &&
//		obj1.y + go1->GetScale().y > obj2.y - halfScale.y  && 
//		obj1.y - go1->GetScale().y < obj2.y + halfScale.y  &&
//		obj1.z + go1->GetScale().z > obj2.z - halfScale.z  &&
//		obj1.z - go1->GetScale().z < obj2.z + halfScale.z )
//	{
//		return true;
//	}
//	return false;
//}
//void CPhysics::collisionResponseBetweenOBJ(Camera3 &camera,CPlayer* &thePlayer, CObj* &go, double dt)
//{
//	Vector3 diffVec = go->getPosition() - thePlayer->GetPosition();
//	if(diffVec.x < 0)
//	{
//		camera.position.x += CAMERA_REPELL;
//		camera.target.x += CAMERA_REPELL ;
//	}
//
//	if(diffVec.x > 0)
//	{
//		camera.position.x -= CAMERA_REPELL;
//		camera.target.x -= CAMERA_REPELL;
//	}
//
//	if(diffVec.z < 0)
//	{
//		camera.position.z += CAMERA_REPELL;
//		camera.target.z += CAMERA_REPELL;
//	}
//
//	if(diffVec.z > 0)
//	{
//		camera.position.z -= CAMERA_REPELL;
//		camera.target.z -= CAMERA_REPELL ;
//	}
//}

// Check height of terrain
const float CPhysics::GetHeightMapY(float x, float z, std::vector<unsigned char> &heightMap,const Vector3& terrainSize )
{
	return m_fOffset* (ReadHeightMap(heightMap, x/terrainSize.x, z/terrainSize.z));
}

// Set player height from terrain
void  CPhysics::setPlayerHeight(Camera3& camera,CPlayer*& thePlayer, std::vector<unsigned char> &heightMap,const Vector3& terrainSize, bool IgnoreHM )
{
	float tempY;
	if (IgnoreHM == false)
	{
		tempY = GetHeightMapY(thePlayer->GetPosition().x, thePlayer->GetPosition().z, heightMap, terrainSize);
	}
	else
	{
		tempY = thePlayer->GetPosition().y;
	}
	
	float diffY = tempY - thePlayer->GetPosition().y;
	camera.position.y += diffY;
	camera.target.y += diffY;
	thePlayer->SetPositionY(tempY);

	cout << "diffY: " << diffY << endl;
}
