#pragma once
#include "node.h"
#include "Model.h"
#include "Transform.h"
//#include <list>

#include <vector>
using namespace std;

class CSceneManager;

class CSceneNode :
	public CNode
{
public:
	enum FSM {
		ATTACK,
		MOVE,
		IDLE,
		NUM_FSM
	};
	enum FLOCKING {
		SEPARATION,
		COHESION,
		IGNORING,
		NUM_FLOCKING
	};

private:
	vector<CNode*> theChildren;

	FSM currentFSM;
	FLOCKING currentFLOCKING;

	CModel* theModel;
	CTransform* theTransform;
	int sceneNodeID;
	bool m_bActive;
	int healthPoints;
	float timeDead;
	bool crowned;
	Vector3 vel;
	float walkDistanceLeft;
	float flickeringTimeLeft;
	float flickeringSubTimeLeft;
	bool toRender;
	float timeIdling;

	// Check where a line segment between two positions interacts a plane
	int GetIntersection(float fDst1, float fDst2, Vector3 P1, Vector3 P2, Vector3 &Hit);
	// Check two positions are within a box region
	int InBox(Vector3 Hit, Vector3 B1, Vector3 B2, const int Axis);

public:
	vector<Vector3> currentGridIndex;

	CSceneNode(void);
	CSceneNode(const int sceneNodeID);
	~CSceneNode(void);

	// Draw this Node and its children
	void Draw(void);
	void Draw(CSceneManager* theSceneManager = NULL, bool m_bLight = false);

	// Set model and other info to this Node
	void SetModel(CModel* theModel);
	int SetNode(CTransform* aNewTransform, CModel* aNewModel, int healthPoints = 5);
	void SetSceneNodeID(const int sceneNodeID);
	// Set textureID
	void SetTextureID(unsigned int textureID);

	int AddChild(CTransform* aNewTransform, CModel* aNewModel);
	int AddChild(const int sceneNodeID, CTransform* aNewTransform, CModel* aNewModel);

	// Get methods
	int GetSceneNodeID(void);
	CSceneNode* GetNode(const int sceneNodeID);

	// Apply transformation to this Node and its children
	void SetTranslation(const float px, const float py, const float pz);
	void ApplyTranslate(const float dx, const float dy, const float dz);
	void ApplyRotate(const float angle, const float rx, const float ry, const float rz, bool self = true);
	void SetScale(const float sx, const float sy, const float sz);

	// Get top left corner of the group
	Vector3 GetTopLeft(void);
	// Get bottom right corner of the group
	Vector3 GetBottomRight(void);

	// Set colour of the instance
	void SetColor(const float red, const float green, const float blue);

	// Return the number of children in this group
	int GetNumOfChild(void);
	// Get top left corner of a child
	bool GetTopLeft(const int m_iChildIndex, Vector3& vector3D_TopLeft);
	// Get bottom right corner of a child
	bool GetBottomRight(const int m_iChildIndex, Vector3& vector3D_BottomRight);

	// Set the Colour of a child
	void SetColorForChild(const int m_iChildIndex, const float red, const float green, const float blue);

	// PrintSelf
	void PrintSelf(void);

	// Return offset
	Vector3 GetOffset(void);

	// Check a position for collision with objects in any grids
	bool CheckForCollision(Vector3 position, int hitPoints);

	// Check two positions for collision with objects in any grids
	int CheckForCollision(Vector3 L1, Vector3 L2, Vector3 &Hit, int hitPoints);

	// Check object for collision with objects in any grids
	bool CheckForCollision(CSceneNode* object, int hitPoints);

	// Get status of the object
	bool GetStatus();
	// Set status of the object
	void SetStatus(bool active);
	// Get time Dead of the object
	float GetTimeDead();
	// Set time Dead of the object
	void SetTimeDead(float timeDead);

	// Get healthpoints
	int GetHealth();

	// Update the time for object to respawn
	void UpdateDead(const double dt);

	// Update the flicking of object
	void UpdateFlickering(const double dt);
	// Get flicking time left of the object
	float GetFlickeringTimeLeft()
	{
		return flickeringTimeLeft;
	};

	// Update the SceneNode
	void Update(const int resolutiionType);

	// Get if object crowned
	bool GetCrowned();
	// Set if object crowned
	void SetCrowned(bool crowned);
	// Get object velocity
	Vector3 GetVel();
	// Set object random velocity
	void SetRandomVel(void);
	// Set object random position
	void SetRandomPos(const vector<CSceneNode*> list, const float Xsize, const float Zsize);
	// Give object random velocity
	void SetRandomDir(void);
	// Get object walk distance left
	float GetWalkDistanceLeft();
	// Set object walk distance left
	void SetWalkDistanceLeft(float walkDistanceLeft);

	// Set Transform
	void SetTransform(CTransform transform);


	// Update the SceneNode FSM
	void UpdateFSM(const float dt, CSceneNode* theAvatarNode);

	// Take Damage
	void TakeDamage(int hitPoints);
};
