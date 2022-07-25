#pragma once
#ifndef SPRING_SOLVER_H
#define SPRING_SOLVER_H

// System Includes
#include <vector>

// Model Includes
#include "Particle.h" 
#include "Anchor.h"

class SpringSolver 
{
public:
	// ctor/dtor
	SpringSolver();
	~SpringSolver();

	// getters/setters
	void set_damping_force(glm::vec3 new_damping_force);

	void set_particle(Particle* particle);
	Particle* get_particle() const { return particle; }

	void set_anchor(Anchor* anchor);
	Anchor* get_anchor() const { return anchor; }


	void update_system(float dt);
	


private:
	// member functions
	void euler_step(float h);

	// memeber vars
	Particle* particle;
	Anchor* anchor;
	glm::vec3 damping_force;
	


};

#endif // !SPRING_SOLVER_H