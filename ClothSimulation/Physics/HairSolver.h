#pragma once
#ifndef HAIR_SOLVER_H
#define HAIR_SOLVER_H

// System Includes
#include <vector>

// Model Includes
#include "Particle.h" 
#include "Anchor.h"

class HairSolver
{
public:
	// ctor/dtor
	HairSolver();
	~HairSolver();

	// getters/setters
	void set_damping_force(glm::vec3 new_damping_force);

	void set_particle_one(Particle* particle);
	Particle* get_particle_one() const { return particle_one; }
	void set_particle_two(Particle* particle);
	Particle* get_particle_two() const { return particle_two; }

	void set_anchor(Anchor* anchor);
	Anchor* get_anchor() const { return anchor; }


	void update_system(float dt);



private:
	// member functions
	void euler_step(float h);

	// memeber vars
	Particle* particle_one;
	Particle* particle_two;
	Anchor* anchor;
	glm::vec3 damping_force;



};

#endif // !HAIR_SOLVER_H