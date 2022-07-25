#pragma once
#ifndef SCENE_H
#define SCENE_H
// System Includes
#include <vector>
#include <glm/vec3.hpp>

// Model Includes
#include "../Shapes/Geometry.h"
#include "Renderer.h"
#include "Shader.h"
#include "Camera.h"
#include "../Shapes/Sphere.h"
#include "../Physics/HairSolver.h"


class Scene {
public:
	Camera camera;

	Scene() : solver(HairSolver()) { }
	Scene(Camera Camera) : camera(Camera) {}
	~Scene() {}

	void set_solver(HairSolver solver) { this->solver = solver; }
	void add_geometry(Sphere* new_geo);
	void update(float dt);
	void render(Renderer* renderer);

	std::vector<Sphere*> geometry;

	HairSolver solver;
	
};

#endif // !SCENE_H
