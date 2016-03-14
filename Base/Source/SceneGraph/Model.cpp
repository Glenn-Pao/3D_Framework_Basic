#include "Model.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library

#include <stdio.h>
#include "..\MeshBuilder.h"

CModel::CModel(void)
	: m_cModelMesh(NULL)
	, m_iCurrentResolution(RESOLUTION_HIGH)
	, theArrayOfMeshes(NULL)
{
	vTopLeft = Vector3( 1.0f, 1.0f, 1.0f );
	vBottomRight = Vector3( -1.0f, -1.0f, -1.0f );
	red = 128;
	green = 255;
	blue = 0;

	theArrayOfMeshes = new Mesh*[NUM_RESOLUTION];
	for (int i = 0; i < NUM_RESOLUTION; i++)
	{
		theArrayOfMeshes[i] = NULL;
	}
}

CModel::~CModel(void)
{
	// Delete thearray of meshes
	if (theArrayOfMeshes != NULL)
	{
		for (int i = 0; i < NUM_RESOLUTION; i++)
		{
			delete theArrayOfMeshes[i];
		}
		delete[] theArrayOfMeshes;
		theArrayOfMeshes = NULL;
	}
	if (m_cModelMesh != NULL)
	{
		delete m_cModelMesh;
		m_cModelMesh = NULL;
	}
}

void CModel::Init(Mesh* newMesh, Mesh* newLowMesh, Mesh* newMediumMesh, Mesh* newHighMesh, Vector3 vTopLeft, Vector3 vBottomRight)
{
	m_cModelMesh = newMesh;
	//m_cModelMesh = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);

	// Create the low resolution sphere
	theArrayOfMeshes[RESOLUTION_LOW] = newLowMesh;
	// Create the med resolution sphere
	theArrayOfMeshes[RESOLUTION_MEDIUM] = newMediumMesh;
	// Create the high resolution sphere
	theArrayOfMeshes[RESOLUTION_HIGH] = newHighMesh;

	this->vTopLeft = vTopLeft;
	this->vBottomRight = vBottomRight;
}

void CModel::Draw(bool m_bLight)
{
	if (m_cModelMesh)
		m_cModelMesh->Render();
	else if (theArrayOfMeshes[m_iCurrentResolution])
		theArrayOfMeshes[m_iCurrentResolution]->Render();
}

void CModel::SetColor(const float red, const float green, const float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

// Get the top left of the bounding box of the instance
Vector3 CModel::GetTopLeft(void)
{
	return Vector3(vTopLeft.x, vTopLeft.y, vTopLeft.z);
}

// Get the bottomright of the bounding box of the instance
Vector3 CModel::GetBottomRight(void)
{
	return Vector3(vBottomRight.x, vBottomRight.y, vBottomRight.z);
}

// Get the Mesh
Mesh* CModel::GetMesh(void)
{
	if (m_cModelMesh)
		return m_cModelMesh;
	else if (theArrayOfMeshes[m_iCurrentResolution])
		return theArrayOfMeshes[m_iCurrentResolution];

	return NULL;
}

/********************************************************************************
Get current resolution
********************************************************************************/
int CModel::GetResolution(void)
{
	return m_iCurrentResolution;
}

/********************************************************************************
Set current resolution
********************************************************************************/
void CModel::SetResolution(const int resolutionType)
{
	// Check that the supplied resolutionType is valid before setting it to m_iCurrentResolution
	if ((resolutionType >= RESOLUTION_LOW) && (resolutionType <= RESOLUTION_HIGH))
		m_iCurrentResolution = resolutionType;
}


/********************************************************************************
Set textureID
********************************************************************************/
void CModel::SetTextureID(unsigned int textureID)
{
	if (m_cModelMesh != NULL)
		m_cModelMesh->textureID = textureID;
	if (theArrayOfMeshes[RESOLUTION_LOW] != NULL)
		theArrayOfMeshes[RESOLUTION_LOW]->textureID = textureID;
	if (theArrayOfMeshes[RESOLUTION_MEDIUM] != NULL)
		theArrayOfMeshes[RESOLUTION_MEDIUM]->textureID = textureID;
	if (theArrayOfMeshes[RESOLUTION_HIGH] != NULL)
		theArrayOfMeshes[RESOLUTION_HIGH]->textureID = textureID;
}