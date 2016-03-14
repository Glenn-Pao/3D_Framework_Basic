#include "MeshBuilder.h"
#include <vector>
#include "Vector3.h"
#include <GL\glew.h>

Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	const GLfloat vertex_buffer_data[] = { 
		-lengthX/2,0.0,0.0,
		lengthX/2,0.0,0.0,
		0.0,-lengthY/2,0.0,
		0.0,lengthY/2,0.0,
		0.0,0.0,-lengthZ/2,
		0.0,0.0,lengthZ/2,
	};
	const GLfloat color_buffer_data[] = { 
		1.0,0.0,0.0,
		1.0,0.0,0.0,
		0.0,1.0,0.0,
		0.0,1.0,0.0,
		0.0,0.0,1.0,
		0.0,0.0,1.0,
	};
	const GLuint index_buffer_data[] = {
		0, 1,
		2, 3,
		4, 5,
	};
	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

	mesh->indexSize = sizeof(index_buffer_data) / sizeof(GLuint);

	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float lengthX, float lengthY)
{
	const GLfloat vertex_buffer_data[] = { 
		-0.5,0.5,0.0,
		-0.5,-0.5,0.0,
		0.5,-0.5,0.0,
		0.5,0.5,0.0,
	};
	const GLfloat color_buffer_data[] = { 
		color.r,  color.g,  color.b,
		color.r,  color.g,  color.b,
		color.r,  color.g,  color.b,
		color.r,  color.g,  color.b,
	};
	const GLfloat normal_buffer_data[] = { 
		-0.5,0.5,0.0,
		-0.5,-0.5,0.0,
		0.5,-0.5,0.0,
		0.5,0.5,0.0,
	};
	const GLuint index_buffer_data[] = {
		0, 1, 3,
		2, 3, 1,
	};
	Mesh *mesh = new Mesh(meshName);
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

	mesh->indexSize = sizeof(index_buffer_data) / sizeof(GLuint);

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlice, float radius)
{
	std::vector<Position> vertex_buffer_data;
	std::vector<Color> color_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 360.f / numSlice;
	//float radianPerSlice = Math::DegreeToRadian(360.f) / numSlice;
	Position pos;
	pos.Set(0, 0, 0);
	color_buffer_data.push_back(color);
	vertex_buffer_data.push_back(pos);
	for(unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		color_buffer_data.push_back(color);
		pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(pos);
	}
	for(unsigned slice = 0; slice < numSlice; ++slice)
	{
		index_buffer_data.push_back(slice + 1);
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(slice + 2);
	}

	Mesh *mesh = new Mesh(meshName);
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Position), &vertex_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(Color), &color_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR, float innerR)
{
	std::vector<Position> vertex_buffer_data;
	std::vector<Color> color_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 360.f / numSlice;
	//float radianPerSlice = Math::DegreeToRadian(360.f) / numSlice;
	Position pos;
	for(unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		float theta = slice * degreePerSlice;
		color_buffer_data.push_back(color);
		pos.Set(outerR * cos(Math::DegreeToRadian(theta)), 0, outerR * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(pos);
		
		color_buffer_data.push_back(color);
		pos.Set(innerR * cos(Math::DegreeToRadian(theta)), 0, innerR * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(pos);
	}
	for(unsigned slice = 0; slice < numSlice + 1; ++slice)
	{
		index_buffer_data.push_back(2 * slice + 0);
		index_buffer_data.push_back(2 * slice + 1);
		//index_buffer_data.push_back(2 * slice + 3);
		//index_buffer_data.push_back(2 * slice + 4);
		//index_buffer_data.push_back(2 * slice + 3);
		//index_buffer_data.push_back(2 * slice + 2);
	}

	Mesh *mesh = new Mesh(meshName);
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Position), &vertex_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(Color), &color_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCube(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	const GLfloat vertex_buffer_data[] = { 
		-0.5,0.5,0.5,
		-0.5,-0.5,0.5,
		0.5,-0.5,0.5,
		0.5,0.5,0.5,
		-0.5,0.5,-0.5,
		-0.5,-0.5,-0.5,
		0.5,-0.5,-0.5,
		0.5,0.5,-0.5,
	};
	const GLfloat color_buffer_data[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
	};
	const GLuint index_buffer_data[] = {
		0, 1, 3,
		2, 3, 1,
		3, 2, 7,
		6, 7, 2,
		7, 6, 4,
		5, 4, 6,
		4, 5, 0,
		1, 0, 5,
		4, 0, 7,
		3, 7, 0,
		1, 5, 2,
		6, 2, 5,
	};
	Mesh *mesh = new Mesh(meshName);
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_data), color_buffer_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);

	mesh->indexSize = sizeof(index_buffer_data) / sizeof(GLuint);

	return mesh;
}

Mesh* GenerateCube2(const std::string &meshName)
{
	std::vector<Vector3> vertex_buffer_data;
	std::vector<Vector3> color_buffer_data;
	std::vector<GLuint> index_buffer_data;
	const GLfloat vb[] = { 
		-0.5,0.5,0.5,
		-0.5,-0.5,0.5,
		0.5,-0.5,0.5,
		0.5,0.5,0.5,
		-0.5,0.5,-0.5,
		-0.5,-0.5,-0.5,
		0.5,-0.5,-0.5,
		0.5,0.5,-0.5,
	};
	for(int i = 0; i < 8; ++i)
	{
		vertex_buffer_data.push_back(Vector3(vb[i * 3], vb[i * 3 + 1], vb[i * 3 + 2]));
	}
	const GLfloat cb[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
	};
	for(int i = 0; i < 8; ++i)
	{
		color_buffer_data.push_back(Vector3(cb[i * 3], cb[i * 3 + 1], cb[i * 3 + 2]));
	}
	const GLuint ib[] = {
		0, 1, 3,
		2, 3, 1,
		3, 2, 7,
		6, 7, 2,
		7, 6, 4,
		5, 4, 6,
		4, 5, 0,
		1, 0, 5,
		4, 0, 7,
		3, 7, 0,
		1, 5, 2,
		6, 2, 5,
	};
	for(int i = 0; i < 36; ++i)
	{
		index_buffer_data.push_back(ib[i]);
	}
	Mesh *mesh = new Mesh(meshName);
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vector3), &vertex_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(Vector3), &color_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(unsigned), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, unsigned numStack, unsigned numSlice, float height, float radius)
{
	std::vector<Vector3> vertex_buffer_data;
	std::vector<Vector3> color_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 360.f / numSlice;

	float stackHeight = height / numStack;
	for(unsigned stack = 0; stack <= numStack; ++stack) //stack
	{
		for(unsigned slice = 0; slice <= numSlice; ++slice) //slice
		//for (unsigned theta = 0; theta <= 360; theta += 10) //slice
		{
			float theta = degreePerSlice * slice;
			vertex_buffer_data.push_back(Vector3(radius * cos(Math::DegreeToRadian(theta)), -height / 2 + stack * stackHeight, sin(Math::DegreeToRadian(theta))));
			color_buffer_data.push_back(Vector3(radius * cos(Math::DegreeToRadian(theta)), -height / 2 + stack * stackHeight, sin(Math::DegreeToRadian(theta))));
			//vertex_buffer_data.push_back(sin(Math::DegreeToRadian(theta)), -height / 2 + (stack + 1) * stackHeight, cos(Math::DegreeToRadian(theta)));
		}
	}
	for(unsigned stack = 0; stack < numStack - 1; ++stack) //stack
	{
		for(unsigned slice = 0; slice <= numSlice; ++slice) //slice
		{
			index_buffer_data.push_back(stack * (numSlice + 1) * 2 + slice);
			index_buffer_data.push_back((stack + 1) * (numSlice + 1) * 2 + slice);
		}
	}

	//vertex_buffer_data.push_back(0, height / 2, 0);
	//for(unsigned slice = 0; slice < numSlice; ++slice) //top
	//{
	//	float theta = degreePerSlice * slice;
	//	vertex_buffer_data.push_back(radius * sin(Math::DegreeToRadian(theta)), height / 2, cos(Math::DegreeToRadian(theta)));
	//}
	//vertex_buffer_data.push_back(0, -height / 2, 0);
	//for(unsigned slice = 0; slice < numSlice; ++slice) //bottom
	//{
	//	float theta = degreePerSlice * slice;
	//	vertex_buffer_data.push_back(radius * sin(Math::DegreeToRadian(theta)), -height / 2, cos(Math::DegreeToRadian(theta)));
	//}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vector3), &vertex_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(Vector3), &color_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(unsigned), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, unsigned numStack, unsigned numSlice, float outerR, float innerR)
{
	std::vector<Vector3> vertex_buffer_data;
	std::vector<Vector3> color_buffer_data;
	std::vector<GLuint> index_buffer_data;

	Vertex v;
	float gradStack = 360.f / numStack;
	float gradSlice = 360.f / numSlice;
	unsigned i = 0, j = 0, starti = 0;
	float x1, z1;
	float x2, y2, z2;
	Vector3 n1, t1, b1;
	Vector3 up(0, 1, 0);

	for(unsigned d = 0; d < numStack + 1; d++) {
		starti = i;
		if(d < numStack)
			index_buffer_data.push_back(i);
		else
			index_buffer_data.push_back(0);
		for(unsigned e = 0; e < numSlice; e++) {
			z1 = (float)(outerR * cos((double)d * gradStack * Math::PI / 180));
			x1 = (float)(outerR * sin((double)d * gradStack * Math::PI / 180));
			z2 = (float)((outerR + innerR * cos((double)e * gradSlice * Math::PI / 180)) * cos((double)d * gradStack * Math::PI / 180));
			y2 = (float)(innerR * sin((double)e * gradSlice * Math::PI / 180));
			x2 = (float)((outerR + innerR * cos((double)e * gradSlice * Math::PI / 180)) * sin((double)d * gradStack * Math::PI / 180));
			n1 = Vector3(x2 - x1, y2, z2 - z1);
			n1.Normalize();
			t1 = up.Cross(n1);
			try {
				t1.Normalize();
			}
			catch(DivideByZero) {
				t1.x = 1;
			}
			b1 = n1.Cross(t1);
			if(starti > 0 && d < numStack)
				index_buffer_data.push_back(i);
			else if(d == numStack)
				index_buffer_data.push_back(e);
			if(d < numStack)
			{
				v.position.Set(x2, y2, z2);
				v.color = color;
				v.normal = n1;
				vertex_buffer_data.push_back(v);
				i++;
			}
			if(starti > 0)
				index_buffer_data.push_back(starti - numSlice + e);
		}
		if(starti == 0) {
			index_buffer_data.push_back(starti);
		}
		else if(d < numStack) {
			index_buffer_data.push_back(starti);
			index_buffer_data.push_back(starti - numSlice);
			index_buffer_data.push_back(starti);
			index_buffer_data.push_back(starti);
			index_buffer_data.push_back(starti);
		}
		else {
			index_buffer_data.push_back(0);
			index_buffer_data.push_back(starti - numSlice);
			index_buffer_data.push_back(0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vector3), &vertex_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(Vector3), &color_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(unsigned), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

Mesh* MeshBuilder::GenerateTorus2(const std::string &meshName, unsigned numStack, unsigned numSlice, float outerR, float innerR)
{
	std::vector<Vector3> vertex_buffer_data;
	std::vector<Vector3> color_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float gradStack = (float)(360.f / numStack);
	float gradSlice = (float)(360.f / numSlice);
	unsigned i = 0, j = 0, starti = 0;
	float x1, z1;
	float x2, y2, z2;
	Vector3 n1, t1, b1;
	Vector3 up(0, 1, 0);

	for(unsigned d = 0; d <= numStack; d++) {
		starti = i;
		if(d < numStack)
			index_buffer_data.push_back(i);
		else
			index_buffer_data.push_back(0);
		for(unsigned e = 0; e < numSlice; e++) {
			z1 = (float)(outerR * cos((double)d * gradStack * Math::PI / 180));
			x1 = (float)(outerR * sin((double)d * gradStack * Math::PI / 180));
			z2 = (float)((outerR + innerR * cos((double)e * gradSlice * Math::PI / 180)) * cos((double)d * gradStack * Math::PI / 180));
			y2 = (float)(innerR * sin((double)e * gradSlice * Math::PI / 180));
			x2 = (float)((outerR + innerR * cos((double)e * gradSlice * Math::PI / 180)) * sin((double)d * gradStack * Math::PI / 180));
			n1 = Vector3(x2 - x1, y2, z2 - z1);
			n1.Normalize();
			t1 = up.Cross(n1);
			try {
				t1.Normalize();
			}
			catch(DivideByZero) {
				t1.x = 1;
			}
			b1 = n1.Cross(t1);
			if(starti > 0 && d < numStack)
				index_buffer_data.push_back(i);
			else if(d == numStack)
				index_buffer_data.push_back(e);
			if(d < numStack)
			{
				vertex_buffer_data.push_back(Vector3(x2, y2, z2));
				color_buffer_data.push_back(Vector3(x2, y2, z2));
				i++;
			}
			if(starti > 0)
				index_buffer_data.push_back(starti - numSlice + e);
		}
		if(starti == 0) {
			index_buffer_data.push_back(starti);
		}
		else if(d < numStack) {
			index_buffer_data.push_back(starti);
			index_buffer_data.push_back(starti - numSlice);
			index_buffer_data.push_back(starti);
			index_buffer_data.push_back(starti);
			index_buffer_data.push_back(starti);
		}
		else {
			index_buffer_data.push_back(0);
			index_buffer_data.push_back(starti - numSlice);
			index_buffer_data.push_back(0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vector3), &vertex_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(Vector3), &color_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(unsigned), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}

float sphereX(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}
float sphereY(float phi, float theta)
{
	return sin(Math::DegreeToRadian(phi));
}
float sphereZ(float phi, float theta)
{
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{
	std::vector<Position> vertex_buffer_data;
	std::vector<Color> color_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	float degreePerStack = 180.f / numStack;
	float degreePerSlice = 360.f / numSlice;
	//float radianPerSlice = Math::DegreeToRadian(360.f) / numSlice;
	Position pos;

	for(unsigned stack = 0; stack < numStack + 1; ++stack) //stack //replace with 180 for sphere
	{
		float phi = -90.f + stack * degreePerStack;
		for(unsigned slice = 0; slice < numSlice + 1; ++slice) //slice
		{
			float theta = slice * degreePerSlice;
			pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi, theta));
			color_buffer_data.push_back(color);
			vertex_buffer_data.push_back(pos);
		}
	}
	for(unsigned stack = 0; stack < numStack; ++stack)
	{
		for(unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
			//index_buffer_data.push_back((numSlice + 1) * stack + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * stack + slice + 1);
			//index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;
	
	glGenBuffers(1, &mesh->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Position), &vertex_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, color_buffer_data.size() * sizeof(Color), &color_buffer_data[0], GL_STATIC_DRAW);
	
	glGenBuffers(1, &mesh->indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();

	return mesh;
}