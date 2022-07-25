#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#define GLM_ENABLE_EXPERIMENTAL
// System Includes
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>


// Model Includes
#include "../Shapes/Sphere.h"

class Particle
{
public:

	// ctor/dtor
	Particle(glm::vec3 particle_position = glm::vec3(0.0f), glm::vec3 particle_velocity = glm::vec3(0.0f), glm::vec3 particle_acceleration = glm::vec3(0.0f), 
		float particle_mass = 1.0f, float damping_coefficient = 0.0f, float spring_constant = 1.0f);
	~Particle();
	
	
	// getters/setters
	void set(glm::vec3 particle_position, glm::vec3 particle_velocity, glm::vec3 particle_acceleration, float particle_mass, float damping_coefficient, float spring_constant);
	void set_position(glm::vec3 new_position);
	void set_velocity(glm::vec3 new_velocity);
	void set_acceleration(glm::vec3 new_acceleration);
	void set_mass(float particle_mass);
	void set_spring_constant(float k);
	void set_damping_coefficient(float new_damping_coefficient);
	
	glm::vec3 get_position() const { return position; }
	glm::vec3 get_velocity() const { return velocity; }
	glm::vec3 get_acceleration() const { return acceleration; }
	float get_mass() const { return mass; }
	float get_damping_coefficient() const { return damping_coefficient; }
	float get_spring_constant() const { return spring_constant; }
	Geometry* get_sphere() const { return geometry; }

	// Utility
	void print();

private:

	Geometry* geometry;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	float mass;
	float damping_coefficient;
	float spring_constant;	// k
};

#endif // !PARTICLE_H
