#ifndef FRUSTRUMCULLING_H
#define FRUSTRUMCULLING_H

#include "GL\glew.h"
#include "Mtx44.h"
#include "MyMath.h"

void ExtractFrustum(Mtx44 proj, Mtx44 modl);

bool PointInFrustum( float x, float y, float z );

bool SphereInFrustumBool( float x, float y, float z, float radius );
float SphereInFrustumFloat( float x, float y, float z, float radius );
int SphereInFrustumInt( float x, float y, float z, float radius );

bool CubeInFrustumBool( float x, float y, float z, float size );
bool CubeInFrustumBool( float x, float y, float z, Vector3 size );
int CubeInFrustumInt( float x, float y, float z, float size );
#endif