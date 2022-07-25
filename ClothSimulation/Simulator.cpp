#include "Simulator.h"


Renderer* renderer;
Logger* logger;

// Simulator
// ---------
Simulator::Simulator(unsigned int width, unsigned int height)
{
	this->Width = width;
	this->Height = height;
}

Simulator::~Simulator()
{
	free(current_scene);
}
void Simulator::initSystem() 
{
	this->initRenderer();
	this->current_scene = test_scene_one();
}

// Renderer
// --------
void Simulator::initRenderer()
{
	renderer = new Renderer();
	logger = new Logger();
}

// Input
// -----
void Simulator::ProcessInput(double dt)
{	
	if(this->Keys[GLFW_KEY_W])
		this->current_scene->camera.ProcessKeyboard(FORWARD, dt);
	if (this->Keys[GLFW_KEY_S])
		this->current_scene->camera.ProcessKeyboard(BACKWARD, dt);
	if (this->Keys[GLFW_KEY_A])
		this->current_scene->camera.ProcessKeyboard(LEFT, dt);
	if (this->Keys[GLFW_KEY_D])
		this->current_scene->camera.ProcessKeyboard(RIGHT, dt);
}

void Simulator::ProcessMouse(float xoffset, float yoffset)
{
	this->current_scene->camera.ProcessMouseMovement(xoffset, yoffset);
}

void Simulator::ProcessScroll(float fov)
{
	this->current_scene->camera.ProcessMouseScroll(fov);
}

// Update
// ------
void Simulator::Update(double dt) 
{
	this->current_scene->solver.update_system(dt);
}

// Render
// ------
void Simulator::Render() {
	current_scene->render(renderer);
}
