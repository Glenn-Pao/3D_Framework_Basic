#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3.h"

struct Particle
{
	enum PARTICLE_TYPE
	{
		P_NONE = 0,
		P_SNOW,
		P_TOTAL, //must be last
	};
	PARTICLE_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	bool active;
	float mass;

	Particle(PARTICLE_TYPE typeValue = P_SNOW);
	~Particle();
};

#endif