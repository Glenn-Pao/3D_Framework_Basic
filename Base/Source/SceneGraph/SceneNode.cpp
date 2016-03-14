#include "SceneNode.h"
//#include "..\Scenes\SceneManager.h"
#include "..\Scenes\Master\SceneManager.h"
#include "Vector3.h"

#include <cstdlib>

CSceneNode::CSceneNode(void)
	: theModel(NULL)
	, theChildren(NULL)
	, theTransform(NULL)
	, sceneNodeID(-1)
	, m_bActive(false)
	, healthPoints(0)
	, timeDead(0.f)
	, crowned(false)
	, flickeringTimeLeft(0.f)
	, flickeringSubTimeLeft(0.f)
	, toRender(true)
	, currentFSM(IDLE)
	, currentFLOCKING(IGNORING)
{
	vel.SetZero();
	Math::InitRNG();
	timeIdling = Math::RandFloatMinMax(1.f, 5.f);
}

CSceneNode::CSceneNode(const int sceneNodeID)
{
	CSceneNode();
	SetSceneNodeID( sceneNodeID );
}


CSceneNode::~CSceneNode(void)
{
	if (theChildren.size() != 0)
	{
		CNode* aChild = NULL;
		for (unsigned i=0; i<theChildren.size(); i++)
		{
			aChild = theChildren[i];
			delete aChild;
			aChild = NULL;
		}
		theChildren.clear();
	}

	if (theModel != NULL)
	{
		delete theModel;
		theModel = NULL;
	}

	if (theTransform != NULL)
	{
		delete theTransform;
		theTransform = NULL;
	}
}

void CSceneNode::Draw(void)
{
	if (theTransform)
	{
		theTransform->PreRendering();
		if (theModel)
			theModel->Draw();

		if (theChildren.size() != 0)
		{
			CNode* aChild = NULL;
			for (unsigned i=0; i<theChildren.size(); i++)
			{
				aChild = theChildren[i];
				aChild->Draw();
			}
		}

		theTransform->PostRendering();
	}
}

void CSceneNode::Draw(CSceneManager* theSceneManager, bool m_bLight)
{
	if (toRender == true)
	{
		if (theTransform)
		{
			//theTransform->PreRendering();

			theSceneManager->modelStack.PushMatrix();
			theSceneManager->modelStack.LoadMatrix(theSceneManager->modelStack.Top() * theTransform->GetTransform());
			if (theChildren.size() != 0)
			{
				CNode* aChild = NULL;
				for (unsigned i = 0; i < theChildren.size(); i++)
				{
					aChild = theChildren[i];
					((CSceneNode*)aChild)->Draw(theSceneManager, m_bLight);
				}
			}
			if (theModel)
			{
				theSceneManager->PreRendering(m_bLight, theModel->GetMesh());
				theModel->Draw();
				theSceneManager->PostRendering(theModel->GetMesh());
			}
			theSceneManager->modelStack.PopMatrix();

			//		theTransform->PostRendering();
		}
	}
}

void CSceneNode::SetModel(CModel* theModel)
{
	this->theModel = theModel;
}


/********************************************************************************
Set textureID
********************************************************************************/
void CSceneNode::SetTextureID(unsigned int textureID)
{
	if (theModel)
		theModel->SetTextureID(textureID);

	if (theChildren.size() != 0)
	{
		CSceneNode* aChild = NULL;
		for (unsigned i = 0; i < theChildren.size(); i++)
		{
			aChild = (CSceneNode*)theChildren[i];
			aChild->SetTextureID(textureID);
		}
	}
}

int CSceneNode::SetNode(CTransform* aNewTransform, CModel* aNewModel, int healthPoints)
{
	this->theModel = aNewModel;
	this->theTransform = aNewTransform;

	this->healthPoints = healthPoints;

	// Set sceneNodeID to 1 as this is the root node
	sceneNodeID = 1;
	return sceneNodeID;
}

void CSceneNode::SetSceneNodeID(const int sceneNodeID)
{
	this->sceneNodeID = sceneNodeID;
}

int CSceneNode::AddChild(CTransform* aNewTransform, CModel* aNewModel)
{
	CSceneNode* aNewNode = new CSceneNode();
	aNewNode->SetNode( aNewTransform, aNewModel );
	aNewNode->SetSceneNodeID( sceneNodeID*10 + (theChildren.size()+1) );
	theChildren.push_back( aNewNode );

	return aNewNode->GetSceneNodeID();
}

int CSceneNode::AddChild(const int sceneNodeID, CTransform* aNewTransform, CModel* aNewModel)
{
	CSceneNode* aNewNode = new CSceneNode( sceneNodeID );
	aNewNode->SetNode( aNewTransform, aNewModel );
	theChildren.push_back( aNewNode );

	return aNewNode->GetSceneNodeID();
}

int CSceneNode::GetSceneNodeID(void)
{
	return sceneNodeID;
}

CSceneNode* CSceneNode::GetNode(const int sceneNodeID)
{
	if (this->sceneNodeID == sceneNodeID)
		return this;

	CSceneNode* theTarget = NULL;
	if (theChildren.size() != 0)
	{
		CSceneNode* aChild = NULL;
		for (unsigned i=0; i<theChildren.size(); i++)
		{
			aChild = (CSceneNode*)theChildren[i];

			theTarget = ((CSceneNode*)aChild)->GetNode( sceneNodeID );
			if (theTarget != NULL)
				break;
		}
	}

	return theTarget;
}

void CSceneNode::SetTranslation(const float px, const float py, const float pz)
{
	if (theTransform)
	{
		theTransform->SetPos(px, py, pz);
	}
}

void CSceneNode::ApplyTranslate( const float dx, const float dy, const float dz )
{
	if (theTransform)
	{
		theTransform->SetTranslate(dx, dy, dz);
	}
}


void CSceneNode::ApplyRotate(const float angle, const float rx, const float ry, const float rz, bool self)
{
	if (theTransform)
	{
		theTransform->SetRotate(angle, rx, ry, rz, self);
	}
}


void CSceneNode::SetScale(const float sx, const float sy, const float sz)
{
	if (theTransform)
	{
		theTransform->SetScale(sx, sy, sz);
	}
}


// Get top left corner of the group
Vector3 CSceneNode::GetTopLeft(void)
{
	if (theTransform == NULL)
		return Vector3( theModel->GetTopLeft().x, 
						 theModel->GetTopLeft().y, 
						 theModel->GetTopLeft().z);
	else
	{
		return (theTransform->GetTransform() * theModel->GetTopLeft());
	}
}

// Get bottom right corner of the group
Vector3 CSceneNode::GetBottomRight(void)
{
	if (theTransform == NULL)
		return Vector3( theModel->GetBottomRight().x, 
						 theModel->GetBottomRight().y, 
						 theModel->GetBottomRight().z);
	else
		return (theTransform->GetTransform() * theModel->GetBottomRight());
}

void CSceneNode::SetColor(const float red, const float green, const float blue)
{
	theModel->SetColor(red, green, blue);
}

// Return the number of children in this group
int CSceneNode::GetNumOfChild(void)
{
	return (int)theChildren.size();
}

// Get top left corner of a child
bool CSceneNode::GetTopLeft(const int m_iChildIndex, Vector3& Vector3_TopLeft)
{
	Vector3_TopLeft = Vector3( -999, -999, -999 );
	CSceneNode* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			Vector3_TopLeft = theTransform->GetTransform() * aChild->GetTopLeft();
			return true;
		}
	}
	return false;
}

// Get bottom right corner of a child
bool CSceneNode::GetBottomRight(const int m_iChildIndex, Vector3& Vector3_BottomRight)
{
	Vector3_BottomRight = Vector3( -999, -999, -999 );
	CSceneNode* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			Vector3_BottomRight = theTransform->GetTransform() * aChild->GetBottomRight();
			return true;
		}
	}
	return false;
}

void CSceneNode::SetColorForChild(const int m_iChildIndex, const float red, const float green, const float blue)
{
	CSceneNode* aChild = NULL;
	for (unsigned i=0; i<theChildren.size(); i++)
	{
		aChild = (CSceneNode*)theChildren[i];

		if (aChild->GetSceneNodeID() == m_iChildIndex)
		{
			aChild->SetColor(red, green, blue);
		}
	}
}

// PrintSelf
void CSceneNode::PrintSelf(void)
{
	cout << "CSceneNode::PrintSelf(void)" << endl;
	cout << "===========================" << endl;
	theTransform->PrintSelf();

	if (theChildren.size() != 0)
	{
		CNode* aChild = NULL;
		for (unsigned i=0; i<theChildren.size(); i++)
		{
			cout << "Child #" << i << endl;
			aChild = theChildren[i];
			((CSceneNode*)aChild)->PrintSelf();
		}
	}
}

// Return offset
Vector3 CSceneNode::GetOffset(void)
{
	Vector3 offset;
	theTransform->GetOffset(offset.x, offset.y, offset.z);
	return offset;
}


/********************************************************************************
Get status of the object. true == active, false == Dead
********************************************************************************/
bool CSceneNode::GetStatus(void)
{
	return m_bActive;
}

/********************************************************************************
Set status of the object
********************************************************************************/
void CSceneNode::SetStatus(bool active)
{
	this->m_bActive = active;
}


/********************************************************************************
Get time Dead of the object
********************************************************************************/
float CSceneNode::GetTimeDead()
{
	return timeDead;
}

/********************************************************************************
Set time Dead of the object
********************************************************************************/
void CSceneNode::SetTimeDead(float timeDead)
{
	this->timeDead = timeDead;
}


/********************************************************************************
Get healthpoints
********************************************************************************/
int CSceneNode::GetHealth()
{
	return healthPoints;
}



/********************************************************************************
 Update the time for object to respawn
********************************************************************************/
void CSceneNode::UpdateDead(const double dt)
{
	timeDead -= (float)dt;
	if (timeDead <= 0.f)
	{
		timeDead = 0.f;
	}
}


/********************************************************************************
Check where a line segment between two positions interacts a plane
********************************************************************************/
int CSceneNode::GetIntersection(float fDst1, float fDst2, Vector3 P1, Vector3 P2, Vector3 &Hit)
{
	if ((fDst1 * fDst2) >= 0.0f)
		return 0;
	if (fDst1 == fDst2)
		return 0;
	Hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
	return 1;
}

/********************************************************************************
Check two positions are within a box region
********************************************************************************/
int CSceneNode::InBox(Vector3 Hit, Vector3 B1, Vector3 B2, const int Axis)
{
	if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y)
		return 1;
	if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x)
		return 1;
	if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y)
		return 1;
	return 0;
}

/********************************************************************************
Check a position for collision with objects in any grids
********************************************************************************/
bool CSceneNode::CheckForCollision(Vector3 position, int hitPoints)
{
	if (m_bActive == true && timeDead == 0.f)
	{
		Vector3 ObjectTopLeft = GetTopLeft();
		Vector3 ObjectBottomRight = GetBottomRight();

		if (((ObjectTopLeft.x > position.x) && (ObjectTopLeft.y > position.y) && (ObjectTopLeft.z > position.z)) &&
			((ObjectBottomRight.x < position.x) && (ObjectBottomRight.y < position.y) && (ObjectBottomRight.z < position.z)))
		{
			if (flickeringTimeLeft == 0.f)
			{
				TakeDamage(hitPoints);
				return true;
			}
		}
	}
	return false;
}

/********************************************************************************
Check two positions for collision with objects in any of the grids
********************************************************************************/
int CSceneNode::CheckForCollision(Vector3 position_start, Vector3 position_end, Vector3 &Hit, int hitPoints)
{
	bool gotHit = false;
	if (m_bActive == true && timeDead == 0.f)
	{
		Vector3 ObjectTopLeft = GetTopLeft();
		Vector3 ObjectBottomRight = GetBottomRight();
		if (position_end.x < ObjectBottomRight.x && position_start.x < ObjectBottomRight.x)
			return false;
		else if (position_end.x > ObjectTopLeft.x && position_start.x > ObjectTopLeft.x)
			return false;
		else if (position_end.y < ObjectBottomRight.y && position_start.y < ObjectBottomRight.y)
			return false;
		else if (position_end.y > ObjectTopLeft.y && position_start.y > ObjectTopLeft.y)
			return false;
		else if (position_end.z < ObjectBottomRight.z && position_start.z < ObjectBottomRight.z)
			return false;
		else if (position_end.z > ObjectTopLeft.z && position_start.z > ObjectTopLeft.z)
			return false;
		else if (position_start.x > ObjectBottomRight.x && position_start.x < ObjectTopLeft.x &&
			position_start.y > ObjectBottomRight.y && position_start.y < ObjectTopLeft.y &&
			position_start.z > ObjectBottomRight.z && position_start.z < ObjectTopLeft.z)
		{
			gotHit = true;
		}
		else if ((GetIntersection(position_start.x - ObjectBottomRight.x, position_end.x - ObjectBottomRight.x, position_start,
			position_end, Hit) && InBox(Hit, ObjectBottomRight, ObjectTopLeft, 1))
			|| (GetIntersection(position_start.y - ObjectBottomRight.y, position_end.y - ObjectBottomRight.y, position_start,
			position_end, Hit) && InBox(Hit, ObjectBottomRight, ObjectTopLeft, 2))
			|| (GetIntersection(position_start.z - ObjectBottomRight.z, position_end.z - ObjectBottomRight.z, position_start,
			position_end, Hit) && InBox(Hit, ObjectBottomRight, ObjectTopLeft, 3))
			|| (GetIntersection(position_start.x - ObjectTopLeft.x, position_end.x - ObjectTopLeft.x, position_start,
			position_end, Hit) && InBox(Hit, ObjectBottomRight, ObjectTopLeft, 1))
			|| (GetIntersection(position_start.y - ObjectTopLeft.y, position_end.y - ObjectTopLeft.y, position_start,
			position_end, Hit) && InBox(Hit, ObjectBottomRight, ObjectTopLeft, 2))
			|| (GetIntersection(position_start.z - ObjectTopLeft.z, position_end.z - ObjectTopLeft.z, position_start,
			position_end, Hit) && InBox(Hit, ObjectBottomRight, ObjectTopLeft, 3)))
		{
			gotHit = true;
		}
		if (gotHit && flickeringTimeLeft == 0.f)
		{
			TakeDamage(hitPoints);
			return true;
		}
	}
	return false;
}


/********************************************************************************
Check object for collision with objects in any grids
********************************************************************************/
bool CSceneNode::CheckForCollision(CSceneNode* object, int hitPoints)
{
	bool gotHit = false;
	if (m_bActive == true && object != this && timeDead == 0.f)
	{
		Vector3 topLeft = GetTopLeft();
		Vector3 bottomRight = GetBottomRight();

		Vector3 ObjectTopLeft = object->GetTopLeft();
		Vector3 ObjectBottomRight = object->GetBottomRight();
		Vector3 ObjectCenter = object->GetTopLeft() - (object->GetTopLeft() - object->GetBottomRight()) * 0.5;

		// Center
		if (((topLeft.x > ObjectCenter.x) && (topLeft.y > ObjectCenter.y) && (topLeft.z > ObjectCenter.z)) &&
			((bottomRight.x < ObjectCenter.x) && (bottomRight.y < ObjectCenter.y) && (bottomRight.z < ObjectCenter.z)))
		{
			gotHit = true;
		}

		// Middle Front
		else if (((topLeft.x > ObjectCenter.x) && (topLeft.y > ObjectCenter.y) && (topLeft.z > ObjectTopLeft.z)) &&
			((bottomRight.x < ObjectCenter.x) && (bottomRight.y < ObjectCenter.y) && (bottomRight.z < ObjectTopLeft.z)))
		{
			gotHit = true;
		}
		// Middle Back
		else if (((topLeft.x > ObjectCenter.x) && (topLeft.y > ObjectCenter.y) && (topLeft.z > ObjectBottomRight.z)) &&
			((bottomRight.x < ObjectCenter.x) && (bottomRight.y < ObjectCenter.y) && (bottomRight.z < ObjectBottomRight.z)))
		{
			gotHit = true;
		}
		// Middle Left
		else if (((topLeft.x > ObjectTopLeft.x) && (topLeft.y > ObjectCenter.y) && (topLeft.z > ObjectCenter.z)) &&
			((bottomRight.x < ObjectTopLeft.x) && (bottomRight.y < ObjectCenter.y) && (bottomRight.z < ObjectCenter.z)))
		{
			gotHit = true;
		}
		// Middle Right
		else if (((topLeft.x > ObjectBottomRight.x) && (topLeft.y > ObjectCenter.y) && (topLeft.z > ObjectCenter.z)) &&
			((bottomRight.x < ObjectBottomRight.x) && (bottomRight.y < ObjectCenter.y) && (bottomRight.z < ObjectCenter.z)))
		{
			gotHit = true;
		}


		// Top Upper Left
		else if (((topLeft.x > ObjectTopLeft.x) && (topLeft.y > ObjectTopLeft.y) && (topLeft.z > ObjectTopLeft.z)) &&
			((bottomRight.x < ObjectTopLeft.x) && (bottomRight.y < ObjectTopLeft.y) && (bottomRight.z < ObjectTopLeft.z)))
		{
			gotHit = true;
		}
		// Top Upper Right
		else if (((topLeft.x > ObjectBottomRight.x) && (topLeft.y > ObjectTopLeft.y) && (topLeft.z > ObjectTopLeft.z)) &&
			((bottomRight.x < ObjectBottomRight.x) && (bottomRight.y < ObjectTopLeft.y) && (bottomRight.z < ObjectTopLeft.z)))
		{
			gotHit = true;
		}
		// Top Lower Left
		else if (((topLeft.x > ObjectTopLeft.x) && (topLeft.y > ObjectTopLeft.y) && (topLeft.z > ObjectBottomRight.z)) &&
			((bottomRight.x < ObjectTopLeft.x) && (bottomRight.y < ObjectTopLeft.y) && (bottomRight.z < ObjectBottomRight.z)))
		{
			gotHit = true;
		}
		// Top Lower Right
		else if (((topLeft.x > ObjectBottomRight.x) && (topLeft.y > ObjectTopLeft.y) && (topLeft.z > ObjectBottomRight.z)) &&
			((bottomRight.x < ObjectBottomRight.x) && (bottomRight.y < ObjectTopLeft.y) && (bottomRight.z < ObjectBottomRight.z)))
		{
			gotHit = true;
		}


		// Bottom Upper Left
		else if (((topLeft.x > ObjectTopLeft.x) && (topLeft.y > ObjectBottomRight.y) && (topLeft.z > ObjectTopLeft.z)) &&
			((bottomRight.x < ObjectTopLeft.x) && (bottomRight.y < ObjectBottomRight.y) && (bottomRight.z < ObjectTopLeft.z)))
		{
			gotHit = true;
		}
		// Bottom Upper Right
		else if (((topLeft.x > ObjectBottomRight.x) && (topLeft.y > ObjectBottomRight.y) && (topLeft.z > ObjectTopLeft.z)) &&
			((bottomRight.x < ObjectBottomRight.x) && (bottomRight.y < ObjectBottomRight.y) && (bottomRight.z < ObjectTopLeft.z)))
		{
			gotHit = true;
		}
		// Bottom Lower Left
		else if (((topLeft.x > ObjectTopLeft.x) && (topLeft.y > ObjectBottomRight.y) && (topLeft.z > ObjectBottomRight.z)) &&
			((bottomRight.x < ObjectTopLeft.x) && (bottomRight.y < ObjectBottomRight.y) && (bottomRight.z < ObjectBottomRight.z)))
		{
			gotHit = true;
		}
		// Bottom Lower Right
		else if (((topLeft.x > ObjectBottomRight.x) && (topLeft.y > ObjectBottomRight.y) && (topLeft.z > ObjectBottomRight.z)) &&
			((bottomRight.x < ObjectBottomRight.x) && (bottomRight.y < ObjectBottomRight.y) && (bottomRight.z < ObjectBottomRight.z)))
		{
			gotHit = true;
		}
		if (gotHit && object->flickeringTimeLeft == 0.f)
		{
			object->TakeDamage(hitPoints);
			return true;
		}
		else if (gotHit && hitPoints != 0)
		{
			return true;
		}
	}
	return false;
}


/********************************************************************************
Update the SceneNode
********************************************************************************/
void CSceneNode::Update(const int resolutionType)
{
	if (theModel)
		theModel->SetResolution(resolutionType);

	if (theChildren.size() != 0)
	{
		CNode* aChild = NULL;
		for (unsigned i = 0; i < theChildren.size(); i++)
		{
			aChild = theChildren[i];
			((CSceneNode*)aChild)->Update(resolutionType);
		}
	}
}


/********************************************************************************
Get if object crowned
********************************************************************************/
bool CSceneNode::GetCrowned()
{
	return crowned;
}

/********************************************************************************
Set if object crowned
********************************************************************************/
void CSceneNode::SetCrowned(bool crowned)
{
	this->crowned = crowned;
}

/********************************************************************************
Get object velocity
********************************************************************************/
Vector3 CSceneNode::GetVel()
{
	return vel;
}

/********************************************************************************
Set object random velocity
********************************************************************************/
void CSceneNode::SetRandomVel(void)
{
	int randNo = Math::RandIntMinMax(0, 3);

	switch (randNo)
	{
	case 0:
		vel.x = 10;
		break;
	case 1:
		vel.x = -10;
		break;
	case 2:
		vel.z = 10;
		break;
	case 3:
		vel.z = -10;
		break;
	}

	walkDistanceLeft = 200.f;
}

/********************************************************************************
Set object random position
********************************************************************************/
void CSceneNode::SetRandomPos(const vector<CSceneNode*> list, const float Xsize, const float Zsize)
{
	while (true)
	{
		Vector3 newPos(Math::RandFloatMinMax(0, Xsize), 0, Math::RandFloatMinMax(0, Zsize));

		// if in centre grid
		if (400 < newPos.x && newPos.x < 600 &&
			400 < newPos.z && newPos.z < 600)
			continue;

		SetTranslation(newPos.x, newPos.y, newPos.z);

		// Check list
		int i;
		for (i = 0; i < (int)list.size(); i++)
		{
			if (CheckForCollision(list[i], 0))
			{
				break;
			}
		}
		if (i == list.size())
			break;
	}
}

/********************************************************************************
Give object random velocity
********************************************************************************/
void CSceneNode::SetRandomDir(void)
{
	Mtx44 rotation;
	int randNo = Math::RandIntMinMax(0, 2);

	if (randNo == 0)
	{
		rotation.SetToRotation(90, 0, 1, 0);
	}
	else if (randNo == 1)
	{
		rotation.SetToRotation(-90, 0, 1, 0);
	}
	else if (randNo == 2)
	{
		rotation.SetToRotation(180, 0, 1, 0);
	}
	vel = rotation * vel;
	walkDistanceLeft = 200.f;
}

/********************************************************************************
Get object walk distance left
********************************************************************************/
float CSceneNode::GetWalkDistanceLeft()
{
	return walkDistanceLeft;
}

/********************************************************************************
Set object walk distance left
********************************************************************************/
void CSceneNode::SetWalkDistanceLeft(float walkDistanceLeft)
{
	this->walkDistanceLeft = walkDistanceLeft;
}


/********************************************************************************
Set Transform
********************************************************************************/
void CSceneNode::SetTransform(CTransform transform)
{
	theTransform->SetTransform(transform.GetTransform());
}


/********************************************************************************
Update the flicking of object
********************************************************************************/
void CSceneNode::UpdateFlickering(const double dt)
{
	if (flickeringTimeLeft != 0.f)
	{
		flickeringTimeLeft -= (float)dt;
		flickeringSubTimeLeft += (float)dt;

		if (flickeringSubTimeLeft > 0.05f)
		{
			flickeringSubTimeLeft = 0.f;
			if (toRender == false)
			{
				toRender = true;
			}
			else
			{
				toRender = false;
			}
		}

		if (flickeringTimeLeft < 0.f)
		{
			flickeringTimeLeft = 0.f;
			flickeringSubTimeLeft = 0.f;

			if (toRender == false)
			{
				toRender = true;
			}
		}
	}
}


/********************************************************************************
Update the SceneNode FSM
********************************************************************************/
void CSceneNode::UpdateFSM(const float dt, CSceneNode* theAvatarNode)
{
	float x, y, z;
	theTransform->GetOffset(x, y, z);

	Vector3 distanceVector = theAvatarNode->GetOffset() - Vector3(x, y, z);
	float theDistance = distanceVector.Length();
	// Within attack range
	if (theDistance < 100.0f)
	{
		Vector3 avatarNodeRadius = theAvatarNode->GetOffset() - theAvatarNode->GetBottomRight();
		Vector3 thisNodeRadius = GetOffset() - GetBottomRight();
		avatarNodeRadius.y = thisNodeRadius.y = 0;
		float separationDistance = avatarNodeRadius.Length() + thisNodeRadius.Length();
		// if the player is within this's node Separation Ring, then move away form it!
		if (theDistance < separationDistance)
		{
			currentFLOCKING = SEPARATION;
		}
		// if the player is within this's node Cohesion Ring, then move toward it!
		else if (theDistance <= 100.0f)
		{
			currentFLOCKING = COHESION;
		}
		else
		{
			currentFLOCKING = IGNORING;
		}

		if (currentFSM != ATTACK)
		{
			currentFSM = ATTACK;
		}
	}
	else
	{
		if (currentFSM == ATTACK)
		{
			currentFSM = IDLE;
		}
	}

	switch (currentFSM)
	{
		case ATTACK:
		{
			Vector3 newDirection = theAvatarNode->GetOffset() - Vector3(x, y, z);

			if (currentFLOCKING == COHESION)
			{
				if (newDirection.Length() > 0.0f)
				{
					newDirection = newDirection.Normalize() * 10.0f * dt;

					this->ApplyTranslate(newDirection.x, newDirection.y, newDirection.z);
				}
			}
			else if (currentFLOCKING == SEPARATION)
			{
				if (newDirection.Length() > 0.0f)
				{
					Vector3 avatarNodeRadius = theAvatarNode->GetOffset() - theAvatarNode->GetBottomRight();
					Vector3 thisNodeRadius = GetOffset() - GetBottomRight();
					avatarNodeRadius.y = thisNodeRadius.y = 0;
					float separationDistance = avatarNodeRadius.Length() + thisNodeRadius.Length();
					newDirection = newDirection.Normalize() * separationDistance * dt;

					this->ApplyTranslate(-newDirection.x, -newDirection.y, -newDirection.z);

					if (theAvatarNode->flickeringTimeLeft == 0.0f)
						theAvatarNode->TakeDamage(1);
				}

			}
			// else if (currentFLOCKING == IGNORE)
		}
		break;
		case MOVE:
		{
			ApplyTranslate(GetVel().x * dt, GetVel().y * dt, GetVel().z * dt);
			SetWalkDistanceLeft(GetWalkDistanceLeft() - GetVel().Length() * dt);

			if (GetWalkDistanceLeft() < 0.f)
			{
				SetRandomDir();

				int randNo = Math::RandIntMinMax(0, 1);

				// Idle
				if (randNo == 0)
				{
					currentFSM = IDLE;
					timeIdling = Math::RandFloatMinMax(1.f, 5.f);
				}
				// else Move
			}
		}
		break;
		case IDLE:
		{
			timeIdling -= dt;
			if (timeIdling <= 0)
			{
				int randNo = Math::RandIntMinMax(0, 1);

				// Move
				if (randNo == 0)
				{
					currentFSM = MOVE;
					timeIdling = 0.f;
				}
				// else Idle
			}
		}
		break;
	}
}


/********************************************************************************
Take Damage
********************************************************************************/
void CSceneNode::TakeDamage(int hitPoints)
{
	healthPoints -= hitPoints;
	if (healthPoints <= 0)
	{
		healthPoints = 5;
		if (crowned == true)
			m_bActive = false;
		else
			timeDead = 5.f;

		currentFSM = IDLE;
		timeIdling = Math::RandFloatMinMax(1.f, 5.f);
	}
	else if (hitPoints != 0.f)
	{
		flickeringTimeLeft = 1.0f;
	}
}