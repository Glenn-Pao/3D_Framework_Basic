#include "Transform.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library

#include <iostream>
using namespace std;

CTransform::CTransform(void)
{
	Mtx.SetToZero();
	Mtx.SetToIdentity();
	Update_Mtx.SetToZero();
	Update_Mtx.SetToIdentity();
}

CTransform::CTransform( const float dx, const float dy, const float dz )
{
	Mtx.SetToTranslation( dx, dy, dz );
}

CTransform::~CTransform(void)
{
}

void CTransform::PreRendering()
{
	glPushMatrix();
	glMultMatrixf(Mtx.a);
}

void CTransform::Draw(void)
{
}

void CTransform::PostRendering()
{
	glPopMatrix();
}

void CTransform::SetPos(const float px, const float py, const float pz)
{
	Mtx.a[12] = px;
	Mtx.a[13] = py;
	Mtx.a[14] = pz;
}

void CTransform::SetTranslate(const float dx, const float dy, const float dz)
{
	/*Mtx44 TempMtx;
	TempMtx.SetToTranslation( dx, dy, dz );

	Mtx = Mtx * TempMtx;*/

	Mtx.a[12] += dx;
	Mtx.a[13] += dy;
	Mtx.a[14] += dz;
}

void CTransform::SetRotate( const float angle, const float rx, const float ry, const float rz, bool self)
{
	Mtx44 MtxBackToPosition;
	if (self)
	{
		Mtx44 MtxBackToOrigin;
		MtxBackToOrigin.a[12] = -Mtx.a[12];
		MtxBackToOrigin.a[13] = -Mtx.a[13];
		MtxBackToOrigin.a[14] = -Mtx.a[14];

		MtxBackToPosition.a[12] = Mtx.a[12];
		MtxBackToPosition.a[13] = Mtx.a[13];
		MtxBackToPosition.a[14] = Mtx.a[14];

		Mtx = Mtx + MtxBackToOrigin;
	}
	Mtx44 TempMtx;
	TempMtx.SetToRotation(angle, rx, ry, rz);

	Mtx =  Mtx * TempMtx ;

	if (self)
	{
		Mtx = Mtx + MtxBackToPosition;
	}
}

void CTransform::SetScale( const float sx, const float sy, const float sz  )
{
	Mtx.a[0] = sx;
	Mtx.a[5] = sy;
	Mtx.a[10] = sz;
}

void CTransform::GetOffset( float& x, float& y, float& z )
{
	x = Mtx.a[ 12 ];
	y = Mtx.a[ 13 ];
	z = Mtx.a[ 14 ];
}

// Get the transformation matrix
Mtx44 CTransform::GetTransform(void)
{
	return Mtx;
}


/********************************************************************************
Set Transform
********************************************************************************/
void CTransform::SetTransform(Mtx44 transform)
{
	Mtx = transform;
}

void CTransform::PrintSelf(void)
{
	cout << "CTransform::PrintSelf(void)" << endl;
	cout << "===========================" << endl;
	Mtx.PrintSelf();
}