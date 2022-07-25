#include "Particle.h"

///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
Particle::Particle(glm::vec3 particle_position, glm::vec3 particle_velocity, glm::vec3 particle_acceleration, float particle_mass, float damping_coefficient, float spring_constant)
{
	set(particle_position, particle_velocity, particle_acceleration, particle_mass, damping_coefficient, spring_constant);
}



///////////////////////////////////////////////////////////////////////////////
// setters
///////////////////////////////////////////////////////////////////////////////
void Particle::set(glm::vec3 particle_position, glm::vec3 particle_velocity, glm::vec3 particle_acceleration, float particle_mass, float damping_coefficient, float spring_constant)
{
	this->geometry = new Sphere(0.1f, 50, 50, true);
	this->position = particle_position;
	this->velocity = particle_velocity;
	this->acceleration = particle_acceleration;
	this->mass = particle_mass;
	this->damping_coefficient = damping_coefficient;
	this->spring_constant = spring_constant;


	glm::mat4 sphere_xform = glm::mat4(1.0f);
	sphere_xform = glm::translate(sphere_xform, position);
	geometry->set_xform_matrix(sphere_xform);

}

void Particle::set_position(glm::vec3 new_position)
{
	this->position = new_position;
	glm::mat4 xform = glm::mat4(1.0f);
	xform = glm::translate(xform, position);
	geometry->set_xform_matrix(xform);	
}

void Particle::set_velocity(glm::vec3 new_velocity)
{
	this->velocity = new_velocity; 
}

void Particle::set_acceleration(glm::vec3 new_acceleration)
{
	this->acceleration = new_acceleration; 
}

void Particle::set_mass(float particle_mass)
{
	this->mass = particle_mass;
}

void Particle::set_spring_constant(float k)
{
	this->spring_constant = k;
}

void Particle::set_damping_coefficient(float new_damping_coefficient)
{
	this->damping_coefficient = new_damping_coefficient; 
}

void Particle::print()
{
	std::cout << "===== Particle =====\n"
		<< "Position: " << glm::to_string(position) << "\n"
		<< "Velocity: " << glm::to_string(velocity) << "\n"
		<< "Acceleration: " << glm::to_string(acceleration) << "\n"
		<< "Mass: " << mass << "\n"
		<< "Damping Coefficient: " << damping_coefficient << "\n"
		<< "Spring Constant: " << spring_constant << "\n";

}


///////////////////////////////////////////////////////////////////////////////
// dtor
///////////////////////////////////////////////////////////////////////////////
Particle::~Particle()
{
	free(geometry);
}