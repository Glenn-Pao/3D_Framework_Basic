#pragma once

#include "Vector3.h"
#include "GL\glew.h"
#include "..\Mesh.h"
#include "Mtx44.h"

class CModel
{
private:
	Vector3 vTopLeft, vBottomRight;
	float red, green, blue;
	
	// Handle to the Mesh
	Mesh* m_cModelMesh;
	Mesh** theArrayOfMeshes;

	// Current resolution
	int m_iCurrentResolution;

public:
	enum RESOLUTION_TYPE
	{
		RESOLUTION_LOW,
		RESOLUTION_MEDIUM,
		RESOLUTION_HIGH,
		NUM_RESOLUTION,
	};

	CModel(void);
	~CModel(void);

	void Init(Mesh* newMesh, Mesh* newLowMesh, Mesh* newMediumMesh, Mesh* newHighMesh, Vector3 vTopLeft, Vector3 vBottomRight);
	void Draw(bool m_bLight = false);
	void SetColor(const float red, const float green, const float blue);

	// Get the top left of the bounding box of the instance
	Vector3 GetTopLeft(void);
	// Get the bottomright of the bounding box of the instance
	Vector3 GetBottomRight(void);
	// Get the Mesh
	Mesh* GetMesh(void);


	// Get current resolution
	int GetResolution(void);
	// Set current resolution
	void SetResolution(const int resolutionType);

	// Set textureID
	void SetTextureID(unsigned int textureID);
};
