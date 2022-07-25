#include "Scene.h"


void Scene::add_geometry(Sphere* new_geo)
{
	this->geometry.push_back(new_geo);
}

void Scene::update(float dt)
{
}

void Scene::render(Renderer* renderer)
{
	// Get Camera/View Matrix
	glm::mat4 view;
	view = this->camera.GetViewMatrix();

	// Get Projection Matrix
	glm::mat4 proj;
	proj = glm::perspective(glm::radians(this->camera.Zoom), (float)1920 / (float)1080, 0.1f, 100.0f);

	Geometry* geo;
	Shader shader;
	Texture2D texture;

	// Spring
	// ------
	geo = solver.get_particle_one()->get_sphere();
	shader = renderer->shader_manager[geo->get_shader_key()];
	texture = renderer->texture_manager[geo->get_texture_key()];
	geo->draw(shader, texture, view, proj);

	// Spring
	// ------
	geo = solver.get_particle_two()->get_sphere();
	shader = renderer->shader_manager[geo->get_shader_key()];
	texture = renderer->texture_manager[geo->get_texture_key()];
	geo->draw(shader, texture, view, proj);


	// Anchor
	// ------
	geo = solver.get_anchor()->get_geometry();
	shader = renderer->shader_manager[geo->get_shader_key()];
	texture = renderer->texture_manager[geo->get_texture_key()];
	geo->draw(shader, texture, view, proj);

}

