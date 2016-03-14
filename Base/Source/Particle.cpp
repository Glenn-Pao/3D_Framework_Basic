#include "Particle.h"

Particle::Particle(PARTICLE_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f)
{

}
Particle::~Particle()
{

}