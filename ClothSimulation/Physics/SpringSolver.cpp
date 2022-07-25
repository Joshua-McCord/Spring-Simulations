#include "SpringSolver.h"

SpringSolver::SpringSolver()
{
	this->particle = new Particle(
		glm::vec3(0.0f, 0.5f, 0.0f),  // Position
		glm::vec3(0.0f),			  // Velocity
		glm::vec3(0.0f),			  // Acceleration
		30,							  // Mass
		2,							  // Damping Coefficient
		2							  // Spring Constant (k)
	);
	this->anchor = new Anchor(
		particle->get_position() - glm::vec3(0.0f, 1.0f, 0.0f)
	);
	this->damping_force = glm::vec3(0.0f);
}

SpringSolver::~SpringSolver()
{
	free(this->particle);
}

void SpringSolver::set_damping_force(glm::vec3 new_damping_force)
{
	this->damping_force = damping_force;
}

void SpringSolver::set_particle(Particle* particle)
{
	this->particle = particle;
}

void SpringSolver::set_anchor(Anchor* anchor)
{
	this->anchor = anchor;
}

void SpringSolver::update_system(float dt)
{
	euler_step(0.01f);

}

void SpringSolver::euler_step(float h)
{
	glm::vec3 position		= particle->get_position();
	float k					= particle->get_spring_constant();
	float mass				= particle->get_mass();
	auto anchor_position	= anchor->get_position();

	auto new_acceleration   = (position - anchor_position) * ((-k * mass)) - damping_force;

	particle->set_acceleration(new_acceleration);										// Update Particle Acceleration
	particle->set_velocity(particle->get_velocity() + (particle->get_acceleration() * h));  // Update Particle Acceleration
	particle->set_position(particle->get_position() + (particle->get_velocity() * h));		// Update Particle Position
	damping_force = particle->get_velocity() * particle->get_damping_coefficient();
}