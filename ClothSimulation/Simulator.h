#ifndef SIMULATOR_H
#define SIMULATOR_H
#define _CRT_SECURE_NO_DEPRECATE

// System Includes
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtx/matrix_decompose.hpp>

// Model Includes
#include "Rendering/Renderer.h"
#include "Util/Logger.h"
#include "Util/MathLib.h"
#include "Rendering/Camera.h"
#include "Rendering/Scene.h"
#include "Shapes/Cube.h"
#include "Shapes/Sphere.h"
#include "Physics/HairSolver.h"




class Simulator {
public:
	bool			Keys[1024];
	int				Width, Height;


	Simulator(unsigned int width = 1920, unsigned int height = 1080);
	~Simulator();

	// init sim
	// --------
	void initSystem();
	void initRenderer();

	// updating and rendering
	// ----------------------
	void ProcessInput(double dt);
	void ProcessMouse(float xoffset, float yoffset);
	void ProcessScroll(float fov);
	void Update(double dt);
	void Render();

private:
	Scene* test_scene_one()
	{
		Scene* scene = new Scene(Camera(glm::vec3(0.0f, 0.0f, 3.0f)));

		return scene;
	}

	// Initial Spring Initialization
	Scene* current_scene;

};


#endif // !SIMULATOR_H



