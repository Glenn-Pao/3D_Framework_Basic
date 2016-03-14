#ifndef FOG_H
#define FOG_H

#include "Vertex.h"
#include "Vector3.h"

struct Fog
{
	Color color;		//Fog color
	float start;		//For linear fog
	float end;			//For linear fog
	float density;		//For exponential fog
	int type;			// linear = 0, exp = 1, exp2 = 2
	bool enabled;		//Toggle fog

	Fog()
	{
		color.Set(0.2f, 0.1f, 0.7f);
		start = 10.f;
		end = 1000.f;
		density = 0.001f;
		type = 0;
		enabled = 0;	//diasble fog
	}
};

#endif
