#pragma once
#include "node.h"
#include "Mtx44.h"

class CSceneNode;

class CTransform :
	public CNode
{
private:
	Mtx44 Mtx, Update_Mtx;

public:
	CTransform(void);
	CTransform( const float dx, const float dy, const float dz  );
	~CTransform(void);

	void PreRendering();
	void Draw(void);
	void PostRendering();

	void SetPos(const float px, const float py, const float pz);
	void SetTranslate(const float dx, const float dy, const float dz);
	void SetRotate(const float angle, const float rx, const float ry, const float rz, bool self = true);
	void SetRotate2( const float angle, const float rx, const float ry, const float rz, 
					 const float offset_x, const float offset_y, const float offset_z );
	void SetScale( const float sx, const float sy, const float sz  );
//	void ApplyTransform( Matrix4x4 newMTX );
	void GetOffset( float& x, float& y, float& z );
	// Get the transformation matrix
	Mtx44 GetTransform(void);
	// Set Transform
	void SetTransform(Mtx44 transform);

	void PrintSelf(void);
};
