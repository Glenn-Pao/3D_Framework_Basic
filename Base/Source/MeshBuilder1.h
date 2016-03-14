#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, unsigned numSlice, float radius);
	static Mesh* GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR, float innerR);
	static Mesh* GenerateCube(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateTorus(const std::string &meshName, unsigned numStack, unsigned numSlice, float outerR, float innerR);
	static Mesh* GenerateTorus2(const std::string &meshName, unsigned numStack, unsigned numSlice, float outerR, float innerR);
	static Mesh* GenerateCylinder(const std::string &meshName, unsigned numStack, unsigned numSlice, float height, float radius);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius);
};

#endif