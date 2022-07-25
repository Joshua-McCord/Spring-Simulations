#include "HairSolver.h"

HairSolver::HairSolver()
{
	this->particle_one = new Particle(
		glm::vec3(0.0f, 0.0f, 0.0f),  // Position
		glm::vec3(0.0f),			  // Velocity
		glm::vec3(0.0f),			  // Acceleration
		30,							  // Mass
		2,							  // Damping Coefficient
		2							  // Spring Constant (k)
	);

	this->particle_two = new Particle(
		glm::vec3(0.0f, 0.0f, 0.0f),  // Position
		glm::vec3(0.0f),			  // Velocity
		glm::vec3(0.0f),			  // Acceleration
		30,							  // Mass
		2,							  // Damping Coefficient
		2							  // Spring Constant (k)
	);
	this->anchor = new Anchor(
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	this->damping_force = glm::vec3(0.0f);
}

HairSolver::~HairSolver()
{
	free(this->particle_one);
	free(this->particle_two);
}

void HairSolver::set_damping_force(glm::vec3 new_damping_force)
{
	this->damping_force = damping_force;
}

void HairSolver::set_particle_one(Particle* particle)
{
	this->particle_one = particle;
}

void HairSolver::set_particle_two(Particle* particle)
{
	this->particle_two = particle;
}

void HairSolver::set_anchor(Anchor* anchor)
{
	this->anchor = anchor;
}

void HairSolver::update_system(float dt)
{
	euler_step(0.01f);

}

void HairSolver::euler_step(float h)
{
	glm::vec3 position_one = particle_one->get_position();
	glm::vec3 position_two = particle_two->get_position();
	float k = particle_one->get_spring_constant();
	float mass = particle_one->get_mass();
	auto anchor_position = anchor->get_position();

	glm::vec3 spring_force = -k * (position_one - anchor_position);
	auto new_acceleration = (position_one + anchor_position) * ((-k * mass)) - damping_force;

	auto particle_one_spring_force = -k * (position_one - anchor_position);


	particle_one->set_acceleration(new_acceleration);										// Update Particle Acceleration
	particle_one->set_velocity(particle_one->get_velocity() + (particle_one->get_acceleration() * h));  // Update Particle Acceleration
	particle_one->set_position(particle_one->get_position() + (particle_one->get_velocity() * h));		// Update Particle Position
	damping_force = particle_one->get_velocity() * particle_one->get_damping_coefficient();
}